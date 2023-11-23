MoveOriginDown:
	ld a, [originY]
	add a, 8
	ld [originY], a
	ld a, 1 ; We want the z flag set here for consistency in the other function calling this
	cp 1    ; Confusing, I know. I'm confused too and don't know wtf I'm doing
	ret

MoveOriginLeft:
	ld a, [originX]
	sub a, 8
	ld [originX], a
	ld a, 1
	cp 1
	ret

MoveOriginRight:
	ld a, [originX]
	add a, 8
	ld [originX], a
	ld a, 1
	cp 1
	ret

MoveOriginUp:
	ld a, [originY]
	sub a, 8
	ld [originY], a
	ld a, 1
	cp 1
	ret
