extends Node2D

const HandAreaScene = preload("res://scenes/hand_area.tscn")
const BoardAreaScene = preload("res://scenes/board_area.tscn")

var player_board: PanelContainer
var hand_area: HBoxContainer

func _ready() -> void:
	player_board = BoardAreaScene.instantiate()
	player_board.position = Vector2(190, 330)
	add_child(player_board)

	hand_area = HandAreaScene.instantiate()
	hand_area.position = Vector2(190, 540)
	add_child(hand_area)

	for i in range(3):
		var minion_data = _random_minion()
		player_board.add_minion(minion_data, randf())

	for i in range(5):
		hand_area.add_card(CardDatabase.get_random_card())

	hand_area.card_clicked.connect(_on_hand_card_clicked)
	player_board.minion_clicked.connect(_on_minion_clicked)

func _random_minion() -> CardData:
	var data = CardDatabase.get_random_card()
	while data.type != CardData.CardType.MINION:
		data = CardDatabase.get_random_card()
	return data

func _on_hand_card_clicked(index: int, data: CardData) -> void:
	print("Hand card clicked: %s (index %d)" % [data.card_name, index])

func _on_minion_clicked(minion_ui: PanelContainer) -> void:
	print("Minion clicked: %s" % minion_ui.card_data.card_name)
