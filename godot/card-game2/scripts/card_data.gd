class_name CardData
extends Resource

enum CardType { MINION, SPELL }
enum SpellEffect { NONE, DAMAGE, HEAL, ARMOR }

@export var id: int
@export var card_name: String
@export var cost: int
@export var attack: int
@export var health: int
@export var description: String
@export var type: CardType
@export var effect: SpellEffect = SpellEffect.NONE
@export var value: int = 0

func duplicate_card() -> CardData:
	var copy = CardData.new()
	copy.id = id
	copy.card_name = card_name
	copy.cost = cost
	copy.attack = attack
	copy.health = health
	copy.description = description
	copy.type = type
	copy.effect = effect
	copy.value = value
	return copy
