extends PanelContainer

@onready var cost_label: Label = $VBox/Header/Margin/HBox/CostCircle/CostLabel
@onready var attack_circle: PanelContainer = $VBox/Header/Margin/HBox/AttackCircle
@onready var attack_label: Label = $VBox/Header/Margin/HBox/AttackCircle/AttackLabel
@onready var name_label: Label = $VBox/Body/NameLabel
@onready var desc_label: Label = $VBox/Body/DescLabel
@onready var health_circle: PanelContainer = $VBox/Footer/Margin/HBox/HealthCircle
@onready var health_label: Label = $VBox/Footer/Margin/HBox/HealthCircle/HealthLabel

var card_data: CardData

func setup(data: CardData) -> void:
	card_data = data
	if not is_node_ready():
		await ready
	_refresh()

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
