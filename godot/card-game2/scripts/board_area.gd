extends PanelContainer

signal minion_clicked(minion_ui: PanelContainer)
signal hero_icon_clicked

const MinionUIScene = preload("res://scenes/minion_ui.tscn")
const MAX_BOARD_SIZE := 7

## When true, the left hero icon emits hero_icon_clicked (opponent board).
@export var is_opponent_side: bool = false

@onready var minion_row: HBoxContainer = $Margin/MainRow/MinionRow
@onready var hero_icon_btn: Button = $Margin/MainRow/HeroIcon


func _ready() -> void:
	hero_icon_btn.focus_mode = Control.FOCUS_NONE
	hero_icon_btn.add_theme_font_size_override("font_size", 40)
	var normal := StyleBoxFlat.new()
	normal.corner_radius_top_left = 12
	normal.corner_radius_top_right = 12
	normal.corner_radius_bottom_right = 12
	normal.corner_radius_bottom_left = 12
	normal.border_width_left = 3
	normal.border_width_top = 3
	normal.border_width_right = 3
	normal.border_width_bottom = 3
	normal.border_color = Color(0.855, 0.647, 0.125, 1)
	if is_opponent_side:
		normal.bg_color = Color(0.35, 0.12, 0.12, 1)
		hero_icon_btn.pressed.connect(_on_hero_icon_pressed)
	else:
		normal.bg_color = Color(0.12, 0.22, 0.35, 1)
		hero_icon_btn.mouse_filter = Control.MOUSE_FILTER_IGNORE
	hero_icon_btn.add_theme_stylebox_override("normal", normal)
	var hover := normal.duplicate()
	if is_opponent_side:
		hover.bg_color = Color(0.45, 0.18, 0.18, 1)
	hero_icon_btn.add_theme_stylebox_override("hover", hover)
	var pressed := normal.duplicate()
	if is_opponent_side:
		pressed.bg_color = Color(0.28, 0.08, 0.08, 1)
	hero_icon_btn.add_theme_stylebox_override("pressed", pressed)
	if is_opponent_side:
		var disabled := normal.duplicate()
		disabled.bg_color = Color(0.22, 0.1, 0.1, 0.65)
		hero_icon_btn.add_theme_stylebox_override("disabled", disabled)


func _on_hero_icon_pressed() -> void:
	hero_icon_clicked.emit()


func set_hero_attack_enabled(enabled: bool) -> void:
	if not is_opponent_side:
		return
	hero_icon_btn.disabled = not enabled

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
		if "instance_id" in child and is_equal_approx(child.instance_id, uid):
			minion_row.remove_child(child)
			child.queue_free()
			return

func get_minion_by_uid(uid: float) -> PanelContainer:
	for child in minion_row.get_children():
		if "instance_id" in child and is_equal_approx(child.instance_id, uid):
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
		minion_row.remove_child(child)
		child.queue_free()

func _on_minion_input(event: InputEvent, minion: PanelContainer) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		minion_clicked.emit(minion)
