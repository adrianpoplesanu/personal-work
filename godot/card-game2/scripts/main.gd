extends Node2D

const CardUI = preload("res://scenes/card_ui.tscn")

func _ready() -> void:
	var start_x := 240
	var spacing := 170
	for i in range(5):
		var card_instance = CardUI.instantiate()
		card_instance.position = Vector2(start_x + i * spacing, 260)
		add_child(card_instance)
		card_instance.setup(CardDatabase.get_random_card())
