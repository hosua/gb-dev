CheckInputAll:
	call GetMinMaxX
CheckInputLeft:

    ld a, [wCurKeys]
    and a, PADF_LEFT
	jp z, CheckInputRight

	call SetMoveDelay
	call CheckAllTilesLeft ; z set if empty below
	call z, MoveOriginLeft ; can move if empty
	ret z ; don't move more than once per tick
CheckInputLeftEnd:

CheckInputRight:

    ld a, [wCurKeys]
    and a, PADF_RIGHT
	jp z, CheckInputUp

	call SetMoveDelay
	call CheckAllTilesRight
	call z, MoveOriginRight
	ret z
CheckInputRightEnd:

CheckInputUp:

	ld a, [wCurKeys]
	and a, PADF_UP
	jp z, CheckInputDown

	call GetMinMaxY
	ld a, b
	cp PLAYFIELD_TOP_BORDER
	jp z, CheckInputUpEnd

	call SetMoveDelay
	call CheckAllTilesAbove
	call z, MoveOriginUp
	ret z
CheckInputUpEnd:

CheckInputDown:

	ld a, [wCurKeys]
	and a, PADF_DOWN
	ret z

	call GetMinMaxY
	ld a, c
	cp PLAYFIELD_BOTTOM_BORDER
	jp z, CheckInputDownEnd

	call SetMoveDelay
	call CheckAllTilesBelow
	call z, MoveOriginDown
CheckInputDownEnd:
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
