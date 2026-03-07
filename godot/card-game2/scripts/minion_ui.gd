extends PanelContainer

@onready var cost_circle: PanelContainer = $VBox/Header/Margin/HBox/CostCircle
@onready var cost_label: Label = $VBox/Header/Margin/HBox/CostCircle/CostLabel
@onready var attack_label: Label = $VBox/Header/Margin/HBox/AttackCircle/AttackLabel
@onready var name_label: Label = $VBox/Body/NameLabel
@onready var health_label: Label = $VBox/Footer/Margin/HBox/HealthCircle/HealthLabel

var card_data: CardData
var instance_id: float = 0.0
var can_attack: bool = false

var _style_normal: StyleBoxFlat
var _style_can_attack: StyleBoxFlat
var _style_attackable: StyleBoxFlat

func _ready() -> void:
	_style_normal = get_theme_stylebox("panel").duplicate()

	_style_can_attack = _style_normal.duplicate()
	_style_can_attack.border_color = Color(1, 0.267, 0.267, 1)
	_style_can_attack.shadow_color = Color(1, 0.267, 0.267, 0.6)
	_style_can_attack.shadow_size = 8

	_style_attackable = _style_normal.duplicate()
	_style_attackable.border_color = Color(1, 0.267, 0.267, 1)
	_style_attackable.shadow_color = Color(1, 0.267, 0.267, 0.5)
	_style_attackable.shadow_size = 10

func setup(data: CardData, uid: float = 0.0) -> void:
	card_data = data
	instance_id = uid
	if not is_node_ready():
		await ready
	_refresh()

func _refresh() -> void:
	cost_label.text = str(card_data.cost)
	attack_label.text = str(card_data.attack)
	health_label.text = str(card_data.health)
	name_label.text = card_data.card_name
	cost_circle.visible = card_data.cost > 0

func set_can_attack(value: bool) -> void:
	can_attack = value
	if value:
		add_theme_stylebox_override("panel", _style_can_attack)
	else:
		add_theme_stylebox_override("panel", _style_normal)

func set_attackable(value: bool) -> void:
	if value:
		add_theme_stylebox_override("panel", _style_attackable)
	else:
		add_theme_stylebox_override("panel", _style_normal)

func update_health(new_health: int) -> void:
	card_data.health = new_health
	health_label.text = str(new_health)
