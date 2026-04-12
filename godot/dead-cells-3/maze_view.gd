extends Control

const WorldGenerator = preload("res://world_generator.gd")

const BOARD_W := 600
const BOARD_H := 600
const CELL := 1.0

var _board: Array = []
var _board_w: int = 0
var _board_h: int = 0

var _rng := RandomNumberGenerator.new()

const BG := Color("#0d1117")
const BLOCKED_FILL := Color("#dc2626")
const BLOCKED_STROKE := Color("#991b1b")
const MAZE_FILL := Color("#1e293b")
const EDGE_COLOR := Color("#dc2626")
const EDGE_WIDTH := 2.0


func _ready() -> void:
	custom_minimum_size = Vector2(BOARD_W, BOARD_H)
	_rng.randomize()
	init_world()


func init_world() -> void:
	var data: Dictionary = WorldGenerator.generate_world(BOARD_W, BOARD_H, _rng)
	_board = data.grid
	_board_w = data.width
	_board_h = data.height
	if data.get("level_spec") != null:
		print(JSON.stringify(data.level_spec))
	queue_redraw()


func _input(event: InputEvent) -> void:
	if event is InputEventKey and event.pressed and not event.echo:
		var ke := event as InputEventKey
		# Use physical key so R works regardless of layout; keycode matches web for typical layouts.
		if ke.physical_keycode == KEY_R or ke.keycode == KEY_R:
			init_world()
			get_viewport().set_input_as_handled()


func _draw() -> void:
	draw_rect(Rect2(Vector2.ZERO, Vector2(BOARD_W, BOARD_H)), BG)

	for row in _board_h:
		for col in _board_w:
			var x: float = col * CELL
			var y: float = row * CELL
			var tile: int = _board[row][col]
			if tile == 0:
				_draw_blocked_tile(x, y, CELL)
			else:
				_draw_maze_tile(x, y, tile, CELL)


func _draw_blocked_tile(x: float, y: float, size: float) -> void:
	var r := Rect2(x, y, size, size)
	draw_rect(r, BLOCKED_FILL)
	draw_rect(r, BLOCKED_STROKE, false, 1.0)


func _draw_maze_tile(x: float, y: float, tile: int, size: float) -> void:
	var r := Rect2(x, y, size, size)
	draw_rect(r, MAZE_FILL)

	if not (tile & WorldGenerator.N):
		draw_line(Vector2(x, y), Vector2(x + size, y), EDGE_COLOR, EDGE_WIDTH)
	if not (tile & WorldGenerator.E):
		draw_line(Vector2(x + size, y), Vector2(x + size, y + size), EDGE_COLOR, EDGE_WIDTH)
	if not (tile & WorldGenerator.S):
		draw_line(Vector2(x + size, y + size), Vector2(x, y + size), EDGE_COLOR, EDGE_WIDTH)
	if not (tile & WorldGenerator.W):
		draw_line(Vector2(x, y + size), Vector2(x, y), EDGE_COLOR, EDGE_WIDTH)

