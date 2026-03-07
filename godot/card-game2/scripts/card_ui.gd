extends PanelContainer

@onready var cost_label: Label = $VBox/Header/Margin/HBox/CostCircle/CostLabel
@onready var attack_circle: PanelContainer = $VBox/Header/Margin/HBox/AttackCircle
@onready var attack_label: Label = $VBox/Header/Margin/HBox/AttackCircle/AttackLabel
@onready var name_label: Label = $VBox/Body/NameLabel
@onready var desc_label: Label = $VBox/Body/DescLabel
@onready var health_circle: PanelContainer = $VBox/Footer/Margin/HBox/HealthCircle
@onready var health_label: Label = $VBox/Footer/Margin/HBox/HealthCircle/HealthLabel

var card_data: CardData

var _style_normal: StyleBoxFlat
var _style_playable: StyleBoxFlat

func _ready() -> void:
	var base: StyleBox = get_theme_stylebox("panel")
	_style_normal = base.duplicate()
	# Build playable (blue) style so it always applies regardless of base type
	_style_playable = base.duplicate()
	if _style_playable is StyleBoxFlat:
		var flat: StyleBoxFlat = _style_playable as StyleBoxFlat
		flat.set_border_width_all(3)
		flat.border_color = Color(0.2, 0.4, 1.0, 1.0)
		flat.shadow_color = Color(0.2, 0.4, 1.0, 0.5)
		flat.shadow_size = 6
	else:
		# Fallback: create a StyleBoxFlat with blue border
		var flat_new := StyleBoxFlat.new()
		if _style_normal is StyleBoxFlat:
			var norm: StyleBoxFlat = _style_normal as StyleBoxFlat
			flat_new.bg_color = norm.bg_color
			flat_new.corner_radius_top_left = norm.corner_radius_top_left
			flat_new.corner_radius_top_right = norm.corner_radius_top_right
			flat_new.corner_radius_bottom_right = norm.corner_radius_bottom_right
			flat_new.corner_radius_bottom_left = norm.corner_radius_bottom_left
		flat_new.set_border_width_all(3)
		flat_new.border_color = Color(0.2, 0.4, 1.0, 1.0)
		flat_new.shadow_color = Color(0.2, 0.4, 1.0, 0.5)
		flat_new.shadow_size = 6
		_style_playable = flat_new

func set_playable(playable: bool) -> void:
	if playable and _style_playable:
		add_theme_stylebox_override("panel", _style_playable)
	else:
		if _style_normal:
			add_theme_stylebox_override("panel", _style_normal)

func setup(data: CardData, playable: bool = false) -> void:
	card_data = data
	if not is_node_ready():
		await ready
	_refresh()
	set_playable(playable)

func _refresh() -> void:
	cost_label.text = str(card_data.cost)
	name_label.text = card_data.card_name
	desc_label.text = card_data.description

	var is_minion = card_data.type == CardData.CardType.MINION
	attack_circle.visible = is_minion
	health_circle.visible = is_minion

	if is_minion:
		attack_label.text = str(card_data.attack)
		health_label.text = str(card_data.health)
