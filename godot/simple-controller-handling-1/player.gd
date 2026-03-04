extends CharacterBody2D
## Simple platformer controller. Move with left stick / WASD / arrows, jump with A / Space.

@export var run_speed: float = 280.0
@export var jump_velocity: float = -420.0
@export var gravity_multiplier: float = 1.0

var gravity: float = 980.0

func _physics_process(delta: float) -> void:
	# Apply gravity
	if not is_on_floor():
		velocity.y += gravity * gravity_multiplier * delta

	# Jump (keyboard: Space, gamepad: A / South face button via ui_accept)
	if Input.is_action_just_pressed(&"ui_accept") and is_on_floor():
		velocity.y = jump_velocity

	# Horizontal movement (left stick, WASD, arrows)
	var direction := Input.get_axis(&"ui_left", &"ui_right")
	velocity.x = direction * run_speed if direction != 0.0 else move_toward(velocity.x, 0.0, run_speed * 2.0 * delta)

	move_and_slide()
