extends Sprite2D

var step = 0

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	print_debug("buna dimineata")
	position.x = 50
	position.y = 50
	step = 1


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if (position.x < 50):
		step = 1

	if (position.x > 200):
		step = -1
	position.x += step
