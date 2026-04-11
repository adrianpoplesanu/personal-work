extends Control


func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventKey and event.pressed and not event.echo:
		if event.keycode == KEY_R:
			$Center/VBox/MazeView.regenerate()
			get_viewport().set_input_as_handled()
