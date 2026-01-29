extends Sprite2D

var speed: float = 1.0
var min_x: float = 50.0
var max_x: float = 200.0
var direction: int = 1  # 1 for right, -1 for left

func _ready():
	# Start at min_x position
	position.x = min_x

func _process(delta):
	# Move the icon
	position.x += speed * direction
	
	# Check boundaries and reverse direction
	if position.x >= max_x:
		position.x = max_x
		direction = -1  # Start moving left
	elif position.x <= min_x:
		position.x = min_x
		direction = 1   # Start moving right

