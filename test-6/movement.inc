MoveOriginDown:
	ld a, [originY]
	add a, 8
	ld [originY], a
	ret

MoveOriginLeft:
	ld a, [originX]
	sub a, 8
	ld [originX], a
	ret

MoveOriginRight:
	ld a, [originX]
	add a, 8
	ld [originX], a
	ret

MoveOriginUp:
	ld a, [originY]
	sub a, 8
	ld [originY], a
	ret
