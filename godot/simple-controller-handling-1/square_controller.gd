extends Control
## Moves this node based on controller (gamepad) and keyboard input.
## Attach to a ColorRect or other Control node. Uses ui_left/right/up/down (WASD, arrows, left stick).

@export var speed: float = 400.0

func _process(delta: float) -> void:
	# Works with keyboard (WASD/arrows) and gamepad left stick via default ui_* actions
	var direction := Input.get_vector(&"ui_left", &"ui_right", &"ui_up", &"ui_down")
	position += direction * speed * delta
	# Keep the square on screen (optional)
	_clamp_to_viewport()


func _clamp_to_viewport() -> void:
	var viewport_rect := get_viewport_rect()
	var size_2d := size if size.x > 0 and size.y > 0 else Vector2(50, 50)
	position.x = clampf(position.x, 0.0, viewport_rect.size.x - size_2d.x)
	position.y = clampf(position.y, 0.0, viewport_rect.size.y - size_2d.y)
