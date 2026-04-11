extends Control
## Dead Cells–style level generation: graph/path structure (port of game2.js).
## Rooms as nodes, corridors as edges; 20×20 grid; R regenerates.

const BOARD_SIZE := 20
const TILE_SIZE := 30

const N := 1
const E := 2
const S := 4
const W := 8

var board: Array = []


func _ready() -> void:
	custom_minimum_size = Vector2(BOARD_SIZE * TILE_SIZE, BOARD_SIZE * TILE_SIZE)
	size = custom_minimum_size
	regenerate()


func regenerate() -> void:
	board = _generate_world()
	queue_redraw()


func _draw() -> void:
	var total := Vector2(BOARD_SIZE * TILE_SIZE, BOARD_SIZE * TILE_SIZE)
	draw_rect(Rect2(Vector2.ZERO, total), Color("#0d1117"))

	for row in BOARD_SIZE:
		for col in BOARD_SIZE:
			var x := col * TILE_SIZE
			var y := row * TILE_SIZE
			var tile: int = board[row][col]
			if tile == 0:
				_draw_blocked_tile(x, y)
			else:
				_draw_maze_tile(x, y, tile)


func _draw_blocked_tile(x: float, y: float) -> void:
	var r := Rect2(x, y, TILE_SIZE, TILE_SIZE)
	draw_rect(r, Color("#dc2626"))
	draw_rect(r, Color("#991b1b"), false, 1.0)


func _draw_maze_tile(x: float, y: float, tile: int) -> void:
	var cell := Color("#1e293b")
	var edge_col := Color("#dc2626")
	var edge_w := 2.0
	var ts := float(TILE_SIZE)

	draw_rect(Rect2(x, y, ts, ts), cell)

	if (tile & N) == 0:
		draw_line(Vector2(x, y), Vector2(x + ts, y), edge_col, edge_w)
	if (tile & E) == 0:
		draw_line(Vector2(x + ts, y), Vector2(x + ts, y + ts), edge_col, edge_w)
	if (tile & S) == 0:
		draw_line(Vector2(x + ts, y + ts), Vector2(x, y + ts), edge_col, edge_w)
	if (tile & W) == 0:
		draw_line(Vector2(x, y + ts), Vector2(x, y), edge_col, edge_w)


func _key(r: int, c: int) -> String:
	return "%d,%d" % [r, c]


func _room_center(room: Dictionary) -> Vector2i:
	var rr: int = room["r"]
	var rc: int = room["c"]
	var rw: int = room["w"]
	var rh: int = room["h"]
	return Vector2i(rr + rh / 2, rc + rw / 2)


func _carve_corridor(traversable: Dictionary, r0: int, c0: int, r1: int, c1: int) -> void:
	var r := r0
	var c := c0
	var go_horizontal_first := randf() < 0.5
	if go_horizontal_first:
		while c != c1:
			c += 1 if c1 > c else -1
			traversable[_key(r, c)] = true
		while r != r1:
			r += 1 if r1 > r else -1
			traversable[_key(r, c)] = true
	else:
		while r != r1:
			r += 1 if r1 > r else -1
			traversable[_key(r, c)] = true
		while c != c1:
			c += 1 if c1 > c else -1
			traversable[_key(r, c)] = true


func _generate_world() -> Array:
	var traversable: Dictionary = {}

	var min_rooms := 5
	var max_rooms := 8
	var num_rooms: int = min_rooms + randi() % (max_rooms - min_rooms + 1)
	var padding := 2
	var rooms: Array = []

	for _i in num_rooms:
		var w: int = 2 + randi() % 2
		var h: int = 2 + randi() % 2
		var max_r: int = BOARD_SIZE - padding - h
		var max_c: int = BOARD_SIZE - padding - w
		var span_r: int = maxi(1, max_r - padding)
		var span_c: int = maxi(1, max_c - padding)
		var r: int = padding + randi() % span_r
		var c: int = padding + randi() % span_c
		rooms.append({"r": r, "c": c, "w": w, "h": h})

	for room in rooms:
		var rr: int = room["r"]
		var rc: int = room["c"]
		var rw: int = room["w"]
		var rh: int = room["h"]
		for dr in rh:
			for dc in rw:
				traversable[_key(rr + dr, rc + dc)] = true

	var edges: Array = []
	var connected: Dictionary = {0: true}

	while connected.size() < num_rooms:
		var connected_list: Array = connected.keys()
		var a: int = connected_list[randi() % connected_list.size()]
		var b: int = randi() % num_rooms
		if connected.has(b):
			continue
		edges.append([a, b])
		connected[b] = true

	var extra_edges: int = randi() % 2
	for _i in extra_edges:
		var a2: int = randi() % num_rooms
		var b2: int = randi() % num_rooms
		if a2 == b2:
			continue
		var sorted_pair: Array = [a2, b2]
		sorted_pair.sort()
		var dup := false
		for e in edges:
			if e[0] == sorted_pair[0] and e[1] == sorted_pair[1]:
				dup = true
				break
		if dup:
			continue
		edges.append([a2, b2])

	for pair in edges:
		var i: int = pair[0]
		var j: int = pair[1]
		var A: Vector2i = _room_center(rooms[i])
		var B: Vector2i = _room_center(rooms[j])
		_carve_corridor(traversable, A.x, A.y, B.x, B.y)

	var grid: Array = []
	for row in BOARD_SIZE:
		var line: Array = []
		line.resize(BOARD_SIZE)
		for col in BOARD_SIZE:
			if not traversable.has(_key(row, col)):
				line[col] = 0
				continue
			var openings := 0
			if row > 0 and traversable.has(_key(row - 1, col)):
				openings |= N
			if col < BOARD_SIZE - 1 and traversable.has(_key(row, col + 1)):
				openings |= E
			if row < BOARD_SIZE - 1 and traversable.has(_key(row + 1, col)):
				openings |= S
			if col > 0 and traversable.has(_key(row, col - 1)):
				openings |= W
			line[col] = openings
		grid.append(line)
	return grid
