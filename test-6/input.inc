CheckInputAll:
	call GetMinMaxX
CheckInputLeft:
	; ld a, b
	; cp PLAYFIELD_LEFT_BORDER
	; ret z

    ld a, [wCurKeys]
    and a, PADF_LEFT
	jp z, CheckInputRight

	call SetMoveDelay
	call CheckAllTilesLeft
	call nz, MoveOriginLeft
	ret nz
CheckInputRight:
	; ld a, b
	; cp PLAYFIELD_RIGHT_BORDER
	; ret z

    ld a, [wCurKeys]
    and a, PADF_RIGHT
	jp z, CheckInputUp

	call SetMoveDelay
	call CheckAllTilesRight
	call nz, MoveOriginRight
	ret nz

	call GetMinMaxY
CheckInputUp:
	; ld a, b
	; cp PLAYFIELD_TOP_BORDER
	; ret z

	ld a, [wCurKeys]
	and a, PADF_UP
	jp z, CheckInputDown

	call SetMoveDelay
	call CheckAllTilesAbove
	call nz, MoveOriginUp
	ret nz

CheckInputDown:
	; ld a, c
	; cp PLAYFIELD_BOTTOM_BORDER
	; ret z

	ld a, [wCurKeys]
	and a, PADF_DOWN
	ret z

	call SetMoveDelay
	call CheckAllTilesBelow
	call nz, MoveOriginDown
	ret

UpdateKeys:
	; Poll half the controller
	ld a, P1F_GET_BTN
	call .onenibble
	ld b, a ; B7-4 = 1; B3-0 = unpressed buttons
	
	; Poll the other half
	ld a, P1F_GET_DPAD
	call .onenibble
	swap a ; A3-0 = unpressed directions; A7-4 = 1
	xor a, b ; A = pressed buttons + directions
	ld b, a ; B = pressed buttons + directions
	
	; And release the controller
	ld a, P1F_GET_NONE
	ldh [rP1], a
	
	; Combine with previous wCurKeys to make wNewKeys
	ld a, [wCurKeys]
	xor a, b ; A = keys that changed state
	and a, b ; A = keys that changed to pressed
	ld [wNewKeys], a
	ld a, b
	ld [wCurKeys], a
	ret

.onenibble
	ldh [rP1], a ; switch the key matrix
	call .knownret ; burn 10 cycles calling a known ret
	; -- No idea what the extra ldh are doing --
	; ldh a, [rP1] ; ignore value while waiting for the key matrix to settle
	; ldh a, [rP1]
	ldh a, [rP1] ; this read counts
	or a, $F0 ; A7-4 = 1; A3-0 = unpressed keys
.knownret
	ret
