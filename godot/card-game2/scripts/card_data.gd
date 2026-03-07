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
## Unique id for this card instance in hand/board (0 = not yet in game)
var instance_id: float = 0.0

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
	copy.instance_id = 0.0
	return copy
