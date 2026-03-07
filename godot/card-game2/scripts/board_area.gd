extends PanelContainer

signal minion_clicked(minion_ui: PanelContainer)

const MinionUIScene = preload("res://scenes/minion_ui.tscn")
const MAX_BOARD_SIZE := 7

@onready var minion_row: HBoxContainer = $Margin/MinionRow

func add_minion(data: CardData, uid: float) -> PanelContainer:
	if is_full():
		return null
	var minion = MinionUIScene.instantiate()
	minion_row.add_child(minion)
	minion.setup(data, uid)
	minion.gui_input.connect(_on_minion_input.bind(minion))
	return minion

func remove_minion_by_uid(uid: float) -> void:
	for child in minion_row.get_children():
		if child.instance_id == uid:
			minion_row.remove_child(child)
			child.queue_free()
			return

func get_minion_by_uid(uid: float) -> PanelContainer:
	for child in minion_row.get_children():
		if child.instance_id == uid:
			return child
	return null

func get_minion_at(index: int) -> PanelContainer:
	if index < 0 or index >= minion_row.get_child_count():
		return null
	return minion_row.get_child(index)

func get_minion_count() -> int:
	return minion_row.get_child_count()

func get_all_minions() -> Array:
	return minion_row.get_children()

func is_full() -> bool:
	return minion_row.get_child_count() >= MAX_BOARD_SIZE

func clear_board() -> void:
	for child in minion_row.get_children():
		child.queue_free()

func _on_minion_input(event: InputEvent, minion: PanelContainer) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		minion_clicked.emit(minion)
