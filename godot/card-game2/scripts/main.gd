extends Node2D

const HandAreaScene = preload("res://scenes/hand_area.tscn")
const BoardAreaScene = preload("res://scenes/board_area.tscn")

var player_board: PanelContainer
var opponent_board: PanelContainer
var hand_area: HBoxContainer
var status_container: Control
var player_health_label: Label
var player_mana_label: Label
var opponent_health_label: Label
var opponent_mana_label: Label
var turn_label: Label
var end_turn_btn: Button
var attack_hero_btn: Button


const UI_SCALE := 0.9

func _ready() -> void:
	_build_ui()
	scale = Vector2(UI_SCALE, UI_SCALE)
	GameState.init_game()
	_refresh_ui()

	GameState.state_changed.connect(_refresh_ui)
	GameState.game_over.connect(_on_game_over)

	hand_area.card_clicked.connect(_on_hand_card_clicked)
	player_board.minion_clicked.connect(_on_player_minion_clicked)
	opponent_board.minion_clicked.connect(_on_opponent_minion_clicked)
	end_turn_btn.pressed.connect(_on_end_turn_pressed)
	attack_hero_btn.pressed.connect(_on_attack_hero_pressed)


func _build_ui() -> void:
	# Status bar (top)
	status_container = HBoxContainer.new()
	status_container.position = Vector2(20, 20)
	status_container.add_theme_constant_override("separation", 20)
	add_child(status_container)

	player_health_label = Label.new()
	player_health_label.text = "Health: 30"
	status_container.add_child(player_health_label)

	player_mana_label = Label.new()
	player_mana_label.text = "Mana: 0/0"
	status_container.add_child(player_mana_label)

	opponent_health_label = Label.new()
	opponent_health_label.text = "Opponent Health: 30"
	status_container.add_child(opponent_health_label)

	opponent_mana_label = Label.new()
	opponent_mana_label.text = "Opponent Mana: 0/0"
	status_container.add_child(opponent_mana_label)

	turn_label = Label.new()
	turn_label.text = "Turn 1"
	status_container.add_child(turn_label)

	end_turn_btn = Button.new()
	end_turn_btn.text = "End Turn"
	status_container.add_child(end_turn_btn)

	attack_hero_btn = Button.new()
	attack_hero_btn.text = "Attack Hero"
	status_container.add_child(attack_hero_btn)

	# Opponent board (top)
	opponent_board = BoardAreaScene.instantiate()
	opponent_board.position = Vector2(190, 60)
	add_child(opponent_board)

	# Player board (middle)
	player_board = BoardAreaScene.instantiate()
	player_board.position = Vector2(190, 320)
	add_child(player_board)

	# Hand (bottom)
	hand_area = HandAreaScene.instantiate()
	hand_area.position = Vector2(190, 500)
	add_child(hand_area)


func _refresh_ui() -> void:
	_refresh_status()
	_refresh_hand()
	_refresh_board()


func _refresh_status() -> void:
	player_health_label.text = "Health: %d" % GameState.player_health
	player_mana_label.text = "Mana: %d/%d" % [GameState.player_mana, GameState.player_mana_max]
	opponent_health_label.text = "Opponent Health: %d" % GameState.opponent_health
	opponent_mana_label.text = "Opponent Mana: %d/%d" % [GameState.opponent_mana, GameState.opponent_mana_max]
	turn_label.text = "Turn %d - %s" % [GameState.turn, "Your Turn" if GameState.player_turn else "Opponent Turn"]
	end_turn_btn.disabled = not GameState.player_turn or GameState.is_game_over
	var can_attack_hero: bool = not GameState.selected_minion.is_empty() and bool(GameState.selected_minion.get("can_attack", false))
	attack_hero_btn.disabled = not can_attack_hero or not GameState.player_turn or GameState.is_game_over


func _refresh_hand() -> void:
	hand_area.clear_hand()
	var can_play_cards: bool = GameState.player_turn and not GameState.is_game_over and GameState.selected_minion.is_empty()
	for card in GameState.player_hand:
		hand_area.add_card(card, can_play_cards and card.cost <= GameState.player_mana)


func _refresh_board() -> void:
	# Player board
	player_board.clear_board()
	for entry in GameState.player_board:
		var minion_ui = player_board.add_minion(entry["card"], entry["instance_id"])
		if minion_ui:
			if "set_can_attack" in minion_ui:
				minion_ui.set_can_attack(entry["can_attack"])
			if "set_selected" in minion_ui:
				minion_ui.set_selected(GameState.is_minion_selected(entry["instance_id"]))
			if "set_attackable" in minion_ui:
				minion_ui.set_attackable(false)

	# Opponent board
	opponent_board.clear_board()
	var can_attack: bool = not GameState.selected_minion.is_empty() and bool(GameState.selected_minion.get("can_attack", false))
	for entry in GameState.opponent_board:
		var minion_ui = opponent_board.add_minion(entry["card"], entry["instance_id"])
		if minion_ui and "set_attackable" in minion_ui:
			minion_ui.set_attackable(can_attack and GameState.player_turn)


func _on_hand_card_clicked(index: int, data: CardData) -> void:
	if not GameState.player_turn or GameState.is_game_over:
		return
	if data.cost > GameState.player_mana:
		return
	if not GameState.selected_minion.is_empty():
		return  # busy with attack selection

	if data.type == CardData.CardType.MINION:
		if GameState.player_board.size() >= 7:
			return
		GameState.play_minion(data)
	elif data.type == CardData.CardType.SPELL:
		GameState.play_spell(data)


func _on_player_minion_clicked(minion_ui: PanelContainer) -> void:
	if not GameState.player_turn or GameState.is_game_over:
		return
	if not "instance_id" in minion_ui:
		return
	var uid: float = minion_ui.instance_id
	var entry := _get_player_board_entry(uid)
	if entry.is_empty():
		return
	GameState.select_minion_for_attack(entry)


func _on_opponent_minion_clicked(minion_ui: PanelContainer) -> void:
	if not GameState.player_turn or GameState.is_game_over:
		return
	if not "instance_id" in minion_ui:
		return
	var uid: float = minion_ui.instance_id
	var defender_entry := _get_opponent_board_entry(uid)
	if defender_entry.is_empty():
		return
	if GameState.selected_minion.is_empty() or not GameState.selected_minion.get("can_attack", false):
		return
	GameState.attack_minion(GameState.selected_minion, defender_entry)


func _get_player_board_entry(instance_id: float) -> Dictionary:
	for entry in GameState.player_board:
		if is_equal_approx(entry["instance_id"], instance_id):
			return entry
	return {}


func _get_opponent_board_entry(instance_id: float) -> Dictionary:
	for entry in GameState.opponent_board:
		if is_equal_approx(entry["instance_id"], instance_id):
			return entry
	return {}


func _on_end_turn_pressed() -> void:
	GameState.end_turn()


func _on_attack_hero_pressed() -> void:
	GameState.attack_hero(false)


func _on_game_over(winner: String) -> void:
	if winner == "player":
		print("You win!")
	else:
		print("You lose!")
	# Could show a dialog or restart; for now just print
