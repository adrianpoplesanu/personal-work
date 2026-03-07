class_name CardDatabase
extends Node

static var cards: Array[CardData] = []

static func _static_init() -> void:
	_build_database()

static func _build_database() -> void:
	cards.clear()
	cards.append(_spell(1, "Fireball", 4, "Deal 6 damage", CardData.SpellEffect.DAMAGE, 6))
	cards.append(_spell(2, "Lightning Bolt", 1, "Deal 3 damage", CardData.SpellEffect.DAMAGE, 3))
	cards.append(_spell(3, "Heal", 2, "Restore 5 health", CardData.SpellEffect.HEAL, 5))
	cards.append(_minion(4, "Peasant", 1, 1, 1, "A weak minion"))
	cards.append(_minion(5, "Orc Warrior", 3, 3, 2, "A fierce fighter"))
	cards.append(_minion(6, "Dragon", 8, 8, 8, "A powerful beast"))
	cards.append(_minion(7, "Knight", 4, 3, 5, "A sturdy defender"))
	cards.append(_minion(8, "Goblin", 2, 2, 1, "Quick but fragile"))
	cards.append(_spell(9, "Shield", 1, "Gain 5 armor", CardData.SpellEffect.ARMOR, 5))
	cards.append(_minion(10, "Wolf", 2, 2, 2, "A loyal companion"))

static func get_random_card() -> CardData:
	if cards.is_empty():
		_build_database()
	return cards[randi() % cards.size()].duplicate_card()

static func get_card_by_id(card_id: int) -> CardData:
	for card in cards:
		if card.id == card_id:
			return card.duplicate_card()
	return null

static func _minion(id: int, card_name: String, cost: int, atk: int, hp: int, desc: String) -> CardData:
	var card = CardData.new()
	card.id = id
	card.card_name = card_name
	card.cost = cost
	card.attack = atk
	card.health = hp
	card.description = desc
	card.type = CardData.CardType.MINION
	return card

static func _spell(id: int, card_name: String, cost: int, desc: String, effect: CardData.SpellEffect, val: int) -> CardData:
	var card = CardData.new()
	card.id = id
	card.card_name = card_name
	card.cost = cost
	card.attack = 0
	card.health = 0
	card.description = desc
	card.type = CardData.CardType.SPELL
	card.effect = effect
	card.value = val
	return card
