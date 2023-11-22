
CheckInputLeft:
	ld a, b
	cp PLAYFIELD_LEFT_BORDER
	ret z

    ld a, [wCurKeys]
    and a, PADF_LEFT
	ret z
	call SetMoveDelay
	call CheckAllTilesLeft
	call nz, MoveTetronimoLeft
	ret

CheckInputRight:
	ld a, b
	cp PLAYFIELD_RIGHT_BORDER
	ret z

    ld a, [wCurKeys]
    and a, PADF_RIGHT
	ret z
	call SetMoveDelay
	call CheckAllTilesRight
	call nz, MoveTetronimoRight
	ret

CheckInputUp:
	ld a, b
	cp PLAYFIELD_TOP_BORDER
	ret z

	ld a, [wCurKeys]
	and a, PADF_UP
	ret z
	call SetMoveDelay
	call MoveTetronimoUp
	ret

CheckInputDown:
	ld a, c
	cp PLAYFIELD_BOTTOM_BORDER
	ret z

	ld a, [wCurKeys]
	and a, PADF_DOWN
	ret z
	call SetMoveDelay
	call CheckAllTilesBelow
	call nz, MoveTetronimoDown
	ret

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
