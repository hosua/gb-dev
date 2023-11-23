MoveTetronimoDown:
	ld hl, BOX1		
	call MoveObjDown
	ld hl, BOX2
	call MoveObjDown
	ld hl, BOX3
	call MoveObjDown
	ld hl, BOX4
	call MoveObjDown
	ret

MoveTetronimoLeft:
	ld hl, BOX1		
	call MoveObjLeft
	ld hl, BOX2
	call MoveObjLeft
	ld hl, BOX3
	call MoveObjLeft
	ld hl, BOX4
	call MoveObjLeft
	ret

MoveTetronimoRight:
	ld hl, BOX1		
	call MoveObjRight
	ld hl, BOX2
	call MoveObjRight
	ld hl, BOX3
	call MoveObjRight
	ld hl, BOX4
	call MoveObjRight
	ret

MoveTetronimoUp:
	ld hl, BOX1		
	call MoveObjUp
	ld hl, BOX2
	call MoveObjUp
	ld hl, BOX3
	call MoveObjUp
	ld hl, BOX4
	call MoveObjUp
	ret

; Before calling these move functions, load the object addr into register HL
MoveObjLeft:
	ld bc, OAMA_X
	add hl, bc
    ld a, [hl]
    sub a, 8
    ld [hl], a
	ret
MoveObjRight:
	ld bc, OAMA_X
	add hl, bc
    ld a, [hl]
	add a, 8
    ld [hl], a
	ret
MoveObjDown:
	ld bc, OAMA_Y
	add hl, bc
    ld a, [hl]
	add a, 8
    ld [hl], a
	ret
MoveObjUp:
	ld bc, OAMA_Y
	add hl, bc
    ld a, [hl]
	sub a, 8
    ld [hl], a
	ret
