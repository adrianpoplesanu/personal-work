extends HBoxContainer

signal card_clicked(index: int, card_data: CardData)

const CardUIScene = preload("res://scenes/card_ui.tscn")
const MAX_HAND_SIZE := 10

func add_card(data: CardData, playable: bool = false) -> PanelContainer:
	if get_card_count() >= MAX_HAND_SIZE:
		return null
	var slot = Control.new()
	slot.custom_minimum_size = Vector2(140, 230)

	var card = CardUIScene.instantiate()
	slot.add_child(card)
	card.position = Vector2(0, 30)
	add_child(slot)
	card.setup(data, playable)

	card.mouse_entered.connect(_on_card_hover.bind(card, true))
	card.mouse_exited.connect(_on_card_hover.bind(card, false))
	card.gui_input.connect(_on_card_input.bind(get_child_count() - 1, card))
	return card

func remove_card_at(index: int) -> void:
	if index < 0 or index >= get_child_count():
		return
	var slot = get_child(index)
	remove_child(slot)
	slot.queue_free()
	_rebind_signals()

func get_card_at(index: int) -> PanelContainer:
	if index < 0 or index >= get_child_count():
		return null
	return get_child(index).get_child(0)

func get_card_data_at(index: int) -> CardData:
	var card = get_card_at(index)
	if card:
		return card.card_data
	return null

func get_card_count() -> int:
	return get_child_count()

func clear_hand() -> void:
	for child in get_children():
		remove_child(child)
		child.queue_free()

func _on_card_hover(card: PanelContainer, entered: bool) -> void:
	var tween = create_tween().set_ease(Tween.EASE_OUT).set_trans(Tween.TRANS_CUBIC)
	if entered:
		tween.tween_property(card, "position:y", 0, 0.15)
	else:
		tween.tween_property(card, "position:y", 30, 0.15)

func _on_card_input(event: InputEvent, index: int, card: PanelContainer) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		card_clicked.emit(index, card.card_data)

func _rebind_signals() -> void:
	for i in range(get_child_count()):
		var slot = get_child(i)
		var card = slot.get_child(0) as PanelContainer
		for conn in card.gui_input.get_connections():
			card.gui_input.disconnect(conn.callable)
		card.gui_input.connect(_on_card_input.bind(i, card))
