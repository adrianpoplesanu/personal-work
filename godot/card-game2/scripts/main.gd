extends Node2D

const CardUI = preload("res://scenes/card_ui.tscn")
const MinionUI = preload("res://scenes/minion_ui.tscn")

func _ready() -> void:
	var start_x := 240
	var spacing := 170

	for i in range(5):
		var card_instance = CardUI.instantiate()
		card_instance.position = Vector2(start_x + i * spacing, 400)
		add_child(card_instance)
		card_instance.setup(CardDatabase.get_random_card())

	var minion_spacing := 140
	for i in range(4):
		var minion_instance = MinionUI.instantiate()
		minion_instance.position = Vector2(300 + i * minion_spacing, 100)
		add_child(minion_instance)
		var data = CardDatabase.get_random_card()
		while data.type != CardData.CardType.MINION:
			data = CardDatabase.get_random_card()
		minion_instance.setup(data, randf())
		if i == 0 or i == 2:
			minion_instance.set_can_attack(true)
		if i == 3:
			minion_instance.set_attackable(true)
