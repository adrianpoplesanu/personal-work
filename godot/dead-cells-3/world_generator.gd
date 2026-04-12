extends RefCounted

const N := 1
const E := 2
const S := 4
const W := 8


static func rects_overlap(a: Dictionary, b: Dictionary) -> bool:
	return a.x < b.x + b.w and a.x + a.w > b.x and a.y < b.y + b.h and a.y + a.h > b.y


static func room_center(room: Dictionary) -> Vector2:
	return Vector2(room.x + room.w * 0.5, room.y + room.h * 0.5)


static func point_in_rects(px: float, py: float, rects: Array) -> bool:
	for r in rects:
		if px >= r.x and px < r.x + r.w and py >= r.y and py < r.y + r.h:
			return true
	return false


static func empty_grid(wpx: int, hpx: int) -> Dictionary:
	var grid: Array = []
	for _row in range(hpx):
		var row: Array = []
		row.resize(wpx)
		row.fill(0)
		grid.append(row)
	return {"grid": grid, "width": wpx, "height": hpx, "level_spec": null}


static func generate_world(wpx: int, hpx: int, rng: RandomNumberGenerator = null) -> Dictionary:
	if rng == null:
		rng = RandomNumberGenerator.new()
		rng.randomize()

	const MARGIN := 8
	const MIN_ROOMS := 5
	const MAX_ROOMS := 8
	var num_rooms: int = MIN_ROOMS + rng.randi_range(0, MAX_ROOMS - MIN_ROOMS)

	const MIN_ROOM_W := 28.0
	const MAX_ROOM_W := 110.0
	const MIN_ROOM_H := 28.0
	const MAX_ROOM_H := 110.0

	var corridor_w: float = 10.0 + rng.randf() * 10.0

	var rooms: Array = []
	const MAX_TOTAL_TRIES := 8000
	var tries := 0
	while rooms.size() < num_rooms and tries < MAX_TOTAL_TRIES:
		tries += 1
		var rw: float = MIN_ROOM_W + rng.randf() * (MAX_ROOM_W - MIN_ROOM_W)
		var rh: float = MIN_ROOM_H + rng.randf() * (MAX_ROOM_H - MIN_ROOM_H)
		var rx: float = MARGIN + rng.randf() * maxf(0.001, wpx - 2.0 * MARGIN - rw)
		var ry: float = MARGIN + rng.randf() * maxf(0.001, hpx - 2.0 * MARGIN - rh)
		var candidate := {"x": rx, "y": ry, "w": rw, "h": rh}

		var ok := true
		for other in rooms:
			if rects_overlap(candidate, other):
				ok = false
				break
		if ok:
			rooms.append(candidate)

	var n: int = rooms.size()
	if n < 2:
		return empty_grid(wpx, hpx)

	var rects: Array = []
	for r in rooms:
		rects.append({"x": r.x, "y": r.y, "w": r.w, "h": r.h})

	var edges: Array = []
	var connected: Array = [0]

	while connected.size() < n:
		var a: int = connected[rng.randi_range(0, connected.size() - 1)]
		var b: int = rng.randi_range(0, n - 1)
		if b in connected:
			continue
		edges.append([a, b])
		connected.append(b)

	var extra_edges: int = rng.randi_range(0, 1)
	for _i in range(extra_edges):
		var ea: int = rng.randi_range(0, n - 1)
		var eb: int = rng.randi_range(0, n - 1)
		if ea == eb:
			continue
		var lo: int = mini(ea, eb)
		var hi: int = maxi(ea, eb)
		var dup := false
		for e in edges:
			if mini(e[0], e[1]) == lo and maxi(e[0], e[1]) == hi:
				dup = true
				break
		if dup:
			continue
		edges.append([ea, eb])

	var add_horizontal_run := func(x0: float, y0: float, x1: float, _y1: float, cw: float) -> void:
		var x_min: float = minf(x0, x1)
		var x_max: float = maxf(x0, x1)
		var w: float = x_max - x_min
		if w < 1e-6:
			return
		rects.append({"x": x_min, "y": y0 - cw * 0.5, "w": w, "h": cw})

	var add_vertical_run := func(x0: float, y0: float, _x1: float, y1: float, cw: float) -> void:
		var y_min: float = minf(y0, y1)
		var y_max: float = maxf(y0, y1)
		var h: float = y_max - y_min
		if h < 1e-6:
			return
		rects.append({"x": x0 - cw * 0.5, "y": y_min, "w": cw, "h": h})

	var carve_l_corridor := func(ax: float, ay: float, bx: float, by: float, cw: float, horizontal_first: bool) -> void:
		if horizontal_first:
			add_horizontal_run.call(ax, ay, bx, ay, cw)
			add_vertical_run.call(bx, ay, bx, by, cw)
		else:
			add_vertical_run.call(ax, ay, ax, by, cw)
			add_horizontal_run.call(ax, by, bx, by, cw)

	var edge_horizontal_first: Array = []
	for e in edges:
		var horizontal_first: bool = rng.randf() < 0.5
		edge_horizontal_first.append(horizontal_first)
		var A: Vector2 = room_center(rooms[e[0]])
		var B: Vector2 = room_center(rooms[e[1]])
		carve_l_corridor.call(A.x, A.y, B.x, B.y, corridor_w, horizontal_first)

	var traversable_at_sample := func(col: int, row: int) -> bool:
		var px: float = col + 0.5
		var py: float = row + 0.5
		return point_in_rects(px, py, rects)

	var grid: Array = []
	for row in range(hpx):
		var row_arr: Array = []
		row_arr.resize(wpx)
		for col in range(wpx):
			if not traversable_at_sample.call(col, row):
				row_arr[col] = 0
				continue
			var openings := 0
			if row > 0 and traversable_at_sample.call(col, row - 1):
				openings |= N
			if col < wpx - 1 and traversable_at_sample.call(col + 1, row):
				openings |= E
			if row < hpx - 1 and traversable_at_sample.call(col, row + 1):
				openings |= S
			if col > 0 and traversable_at_sample.call(col - 1, row):
				openings |= W
			row_arr[col] = openings
		grid.append(row_arr)

	var rooms_data: Array = []
	for r in rooms:
		rooms_data.append({"x": r.x, "y": r.y, "w": r.w, "h": r.h})

	var edges_copy: Array = []
	for e in edges:
		edges_copy.append([e[0], e[1]])

	var level_spec := {
		"version": 1,
		"width": wpx,
		"height": hpx,
		"corridor_width": corridor_w,
		"rooms": rooms_data,
		"edges": edges_copy,
		"edge_horizontal_first": edge_horizontal_first,
	}

	return {"grid": grid, "width": wpx, "height": hpx, "level_spec": level_spec}
