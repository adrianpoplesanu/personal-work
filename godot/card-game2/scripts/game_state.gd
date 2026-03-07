extends Node
## Game state and rules logic, following the implementation from card-game1.
## Single source of truth; UI should sync from state when state_changed is emitted.

signal state_changed
signal game_over(winner: String)  # "player" or "opponent"

const MAX_HAND_SIZE := 10
const MAX_BOARD_SIZE := 7
const MAX_HEALTH := 30
const MAX_MANA := 10

# --- State (mirrors card-game1 gameState) ---
var turn: int = 1
var player_turn: bool = true
var player_health: int = 30
var player_mana: int = 1
var player_mana_max: int = 1
var opponent_health: int = 30
var opponent_mana: int = 0
var opponent_mana_max: int = 0
var player_hand: Array[CardData] = []
var opponent_hand: Array[CardData] = []
# Board: array of dicts { instance_id: float, card: CardData, can_attack: bool }
var player_board: Array = []
var opponent_board: Array = []
var selected_minion: Dictionary = {}  # same shape as board entry, empty if none selected
var is_game_over: bool = false

var _next_uid: float = 0.0


func _next_instance_id() -> float:
	_next_uid += 1.0
	return Time.get_ticks_msec() * 0.001 + _next_uid * 0.0001


# --- Init ---
func init_game() -> void:
	turn = 1
	player_turn = true
	player_health = MAX_HEALTH
	player_mana = 1
	player_mana_max = 1
	opponent_health = MAX_HEALTH
	opponent_mana = 0
	opponent_mana_max = 0
	player_hand.clear()
	opponent_hand.clear()
	player_board.clear()
	opponent_board.clear()
	selected_minion = {}
	is_game_over = false
	_next_uid = 0.0

	for i in range(3):
		_draw_card(true)
		_draw_card(false)

	_emit_state_changed()


# --- Draw card ---
func _draw_card(is_player: bool) -> void:
	var hand: Array[CardData] = player_hand if is_player else opponent_hand
	if hand.size() >= MAX_HAND_SIZE:
		return
	var card: CardData = CardDatabase.get_random_card()
	card.instance_id = _next_instance_id()
	hand.append(card)


# --- Play minion from hand to board ---
func play_minion(card: CardData) -> bool:
	if not player_turn or is_game_over:
		return false
	if card.type != CardData.CardType.MINION:
		return false
	var idx := _hand_index_by_instance_id(player_hand, card.instance_id)
	if idx < 0:
		return false
	if player_board.size() >= MAX_BOARD_SIZE:
		return false
	if card.cost > player_mana:
		return false

	var minion_card: CardData = card.duplicate_card()
	minion_card.instance_id = card.instance_id
	var entry := {
		"instance_id": minion_card.instance_id,
		"card": minion_card,
		"can_attack": false
	}
	player_board.append(entry)
	player_mana -= card.cost
	player_hand.remove_at(idx)
	selected_minion = {}
	_emit_state_changed()
	return true


# --- Play spell from hand ---
func play_spell(card: CardData) -> bool:
	if not player_turn or is_game_over:
		return false
	if card.type != CardData.CardType.SPELL:
		return false
	var idx := _hand_index_by_instance_id(player_hand, card.instance_id)
	if idx < 0:
		return false
	if card.cost > player_mana:
		return false

	if card.effect == CardData.SpellEffect.DAMAGE:
		if opponent_board.size() > 0:
			var target: Dictionary = opponent_board[randi() % opponent_board.size()]
			_deal_damage_to_minion(target, card.value)
		else:
			_deal_damage_to_hero(false, card.value)
		_remove_dead_minions()
	elif card.effect == CardData.SpellEffect.HEAL:
		player_health = mini(MAX_HEALTH, player_health + card.value)
	elif card.effect == CardData.SpellEffect.ARMOR:
		player_health = mini(MAX_HEALTH, player_health + card.value)

	player_mana -= card.cost
	player_hand.remove_at(idx)
	_emit_state_changed()
	_check_game_over()
	return true


# --- Attack minion with selected player minion ---
func attack_minion(attacker_entry: Dictionary, defender_entry: Dictionary) -> bool:
	if not player_turn or is_game_over:
		return false
	if selected_minion.is_empty() || attacker_entry["instance_id"] != selected_minion["instance_id"]:
		return false
	if not attacker_entry["can_attack"]:
		return false
	var defender_card: CardData = defender_entry["card"]
	var attacker_card: CardData = attacker_entry["card"]
	print("[ATTACK] Player minion %s attacked %s" % [_format_minion_data(attacker_card), _format_minion_data(defender_card)])

	_deal_damage_to_minion(defender_entry, attacker_card.attack)
	_deal_damage_to_minion(attacker_entry, defender_card.attack)
	attacker_entry["can_attack"] = false
	_remove_dead_minions()
	selected_minion = {}
	_emit_state_changed()
	_check_game_over()
	return true


# --- Attack hero with selected player minion ---
func attack_hero(target_is_player: bool) -> bool:
	if not player_turn or is_game_over or selected_minion.is_empty():
		return false
	if not selected_minion["can_attack"]:
		return false
	var atk: int = selected_minion["card"].attack
	# This function is only called when player attacks opponent hero
	print("[ATTACK] Player minion %s attacked HERO" % [_format_minion_data(selected_minion["card"])])
	_deal_damage_to_hero(target_is_player, atk)
	selected_minion["can_attack"] = false
	selected_minion = {}
	_emit_state_changed()
	_check_game_over()
	return true


func _deal_damage_to_minion(entry: Dictionary, damage: int) -> void:
	var card: CardData = entry["card"]
	card.health -= damage


func _deal_damage_to_hero(is_player: bool, damage: int) -> void:
	if is_player:
		player_health = maxi(0, player_health - damage)
	else:
		opponent_health = maxi(0, opponent_health - damage)


func _remove_dead_minions() -> void:
	player_board = player_board.filter(func(e): return e["card"].health > 0)
	opponent_board = opponent_board.filter(func(e): return e["card"].health > 0)


# --- Select minion for attack (player board only) ---
func select_minion_for_attack(entry: Dictionary) -> void:
	if not player_turn or is_game_over:
		return
	if entry.is_empty():
		selected_minion = {}
		_emit_state_changed()
		return
	if not entry["can_attack"]:
		return
	# Toggle: same minion clicked again = deselect
	if not selected_minion.is_empty() && selected_minion["instance_id"] == entry["instance_id"]:
		selected_minion = {}
	else:
		selected_minion = entry
	_emit_state_changed()


func is_minion_selected(instance_id: float) -> bool:
	return not selected_minion.is_empty() && selected_minion["instance_id"] == instance_id


# --- End turn / opponent turn ---
func end_turn() -> void:
	if not player_turn or is_game_over:
		return
	player_turn = false
	for entry in player_board:
		entry["can_attack"] = true
	_emit_state_changed()
	# Opponent turn runs after a short delay (call from main or use timer)
	call_deferred("_run_opponent_turn")


func _run_opponent_turn() -> void:
	# Turn number is not incremented here; one full round = player + opponent, then we increment in _end_opponent_turn
	opponent_mana_max = mini(MAX_MANA, turn)
	opponent_mana = opponent_mana_max
	if turn > 1:
		_draw_card(false)
	var minions_at_start: Array = opponent_board.map(func(e): return e["instance_id"])
	print("[Opponent] --- Turn %d --- Mana: %d/%d | Hand: %d card(s) [%s] | Board: %d minion(s)" % [turn, opponent_mana, opponent_mana_max, opponent_hand.size(), _format_hand(opponent_hand), opponent_board.size()])
	_emit_state_changed()

	# Simple AI: play cards then attack
	_opponent_play_cards()
	_emit_state_changed()
	# Only minions that were on board at start can attack
	for entry in opponent_board:
		if minions_at_start.has(entry["instance_id"]):
			entry["can_attack"] = true
	_opponent_attack()
	_remove_dead_minions()
	_emit_state_changed()
	_check_game_over()

	# Back to player
	_end_opponent_turn()


func _opponent_play_cards() -> void:
	var playable: Array = []
	for card in opponent_hand:
		if card.cost <= opponent_mana:
			playable.append(card)
	playable.sort_custom(func(a, b): return a.cost > b.cost)

	# Log hand at start of playing
	print("[Opponent] Cards in hand: %d [%s] | Playing up to %d card(s) (mana %d)" % [opponent_hand.size(), _format_hand(opponent_hand), playable.size(), opponent_mana])

	for card in playable:
		if opponent_mana < card.cost:
			continue
		var card_name: String = card.card_name
		var card_type: String = "minion" if card.type == CardData.CardType.MINION else "spell"
		if card.type == CardData.CardType.MINION && opponent_board.size() < MAX_BOARD_SIZE:
			var minion_card: CardData = card.duplicate_card()
			minion_card.instance_id = card.instance_id
			opponent_board.append({
				"instance_id": minion_card.instance_id,
				"card": minion_card,
				"can_attack": false
			})
			opponent_mana -= card.cost
			var idx := _hand_index_by_instance_id(opponent_hand, card.instance_id)
			if idx >= 0:
				opponent_hand.remove_at(idx)
			print("[Opponent] Plays %s (%s, cost %d) -> board. Cards remaining in hand: %d [%s]" % [card_name, card_type, card.cost, opponent_hand.size(), _format_hand(opponent_hand)])
		elif card.type == CardData.CardType.SPELL:
			if card.effect == CardData.SpellEffect.DAMAGE:
				if player_board.size() > 0:
					var target: Dictionary = player_board[randi() % player_board.size()]
					_deal_damage_to_minion(target, card.value)
					_remove_dead_minions()
				else:
					_deal_damage_to_hero(true, card.value)
			elif card.effect == CardData.SpellEffect.HEAL:
				opponent_health = mini(MAX_HEALTH, opponent_health + card.value)
			opponent_mana -= card.cost
			var idx := _hand_index_by_instance_id(opponent_hand, card.instance_id)
			if idx >= 0:
				opponent_hand.remove_at(idx)
			print("[Opponent] Plays %s (%s, cost %d). Cards remaining in hand: %d [%s]" % [card_name, card_type, card.cost, opponent_hand.size(), _format_hand(opponent_hand)])

	print("[Opponent] End of plays. Cards remaining in hand: %d [%s]" % [opponent_hand.size(), _format_hand(opponent_hand)])


func _opponent_attack() -> void:
	var attackers: Array = opponent_board.filter(func(e): return e["can_attack"])
	for entry in attackers:
		if is_game_over:
			break
		_remove_dead_minions()
		if player_board.size() > 0:
			var target: Dictionary = player_board[randi() % player_board.size()]
			var atk: CardData = entry["card"]
			var def: CardData = target["card"]
			print("[ATTACK] Opponent minion %s attacked %s" % [_format_minion_data(atk), _format_minion_data(def)])
			_deal_damage_to_minion(target, atk.attack)
			_deal_damage_to_minion(entry, def.attack)
			entry["can_attack"] = false
			_remove_dead_minions()
		else:
			print("[ATTACK] Opponent minion %s attacked HERO" % [_format_minion_data(entry["card"])])
			_deal_damage_to_hero(true, entry["card"].attack)
			entry["can_attack"] = false


func _end_opponent_turn() -> void:
	player_turn = true
	turn += 1
	player_mana_max = mini(MAX_MANA, turn)
	player_mana = player_mana_max
	_draw_card(true)
	for entry in player_board:
		entry["can_attack"] = true
	_emit_state_changed()


func _format_hand(hand: Array[CardData]) -> String:
	var parts: PackedStringArray = []
	for card in hand:
		parts.append("%s (cost %d)" % [card.card_name, card.cost])
	return ", ".join(parts) if parts.size() > 0 else "none"


func _format_minion_data(card: CardData) -> String:
	return "%s (%d/%d)" % [card.card_name, card.attack, card.health]


func _check_game_over() -> void:
	if is_game_over:
		return
	if player_health <= 0:
		is_game_over = true
		game_over.emit("opponent")
	elif opponent_health <= 0:
		is_game_over = true
		game_over.emit("player")


func _hand_index_by_instance_id(hand: Array[CardData], instance_id: float) -> int:
	for i in range(hand.size()):
		if is_equal_approx(hand[i].instance_id, instance_id):
			return i
	return -1


func _emit_state_changed() -> void:
	state_changed.emit()
