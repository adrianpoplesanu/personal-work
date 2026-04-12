extends Control


func _ready() -> void:
	# So the maze view can use _gui_input as a fallback if needed.
	$CenterContainer/VBox/MazeView.grab_focus()
