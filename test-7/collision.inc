; @param b: X
; @param c: Y
; @return hl: tile address = _SCRN0 + X + Y*32
GetTile:
	ld a, c ; y pos
	ld l, a ; store y pos in right half of hl
	ld h, 0 ; make sure h is zeroed out	

	; Here, we need to multiply Y by 32 because every row has 32 tiles (only 20
	; are shown, but there are actually 32)

	; now we have position on the grid * 8
	add hl, hl ; * 16
	add hl, hl ; * 32
	; Now we have hl = y_pos * 32

	ld a, b   ; x pos * 8
	srl a     ; / 2
	srl a     ; / 4
	srl a     ; / 8
	; a = x_pos
	
	ld e, a
	ld a, 0
	ld d, a
	add hl, de ; now we have hl = x_pos + y_pos * 32
	ld de, _SCRN0
	add hl, de ; hl = _SCRN0 + x_pos + y_pos * 32
	ret

; @return: z flag unset if tile below, nz flag set if tile is non-empty
CheckAllTilesAbove:
	ld hl, BOX1
	call CheckTileAbove ; z flag unset if empty tile detected
	ret nz
	ld hl, BOX2
	call CheckTileAbove
	ret nz
	ld hl, BOX3
	call CheckTileAbove
	ret nz
	ld hl, BOX4
	call CheckTileAbove
	ret

; @return: z flag unset if tile below, nz flag set if tile is non-empty
CheckAllTilesBelow:
	ld hl, BOX1
	call CheckTileBelow ; z flag unset if empty
	ret nz
	ld hl, BOX2
	call CheckTileBelow
	ret nz
	ld hl, BOX3
	call CheckTileBelow
	ret nz
	ld hl, BOX4
	call CheckTileBelow
	ret

; @return: z flag unset if tile below, nz flag set if tile is non-empty
CheckAllTilesLeft:
	ld hl, BOX1
	call CheckTileLeft
	ret nz
	ld hl, BOX2
	call CheckTileLeft
	ret nz
	ld hl, BOX3
	call CheckTileLeft
	ret nz
	ld hl, BOX4
	call CheckTileLeft
	ret

; @return: z flag unset if tile below, nz flag if not
CheckAllTilesRight:
	ld hl, BOX1
	call CheckTileRight
	ret nz
	ld hl, BOX2
	call CheckTileRight
	ret nz
	ld hl, BOX3
	call CheckTileRight
	ret nz
	ld hl, BOX4
	call CheckTileRight
	ret	

; @param: hl: address of object
; @return: store data at tile address in reg a, also set compare flag to 0 if placed tile detected
CheckTileAbove:
	ld a, [hli] ; OBJ_Y
	sub a, 16 + 8
	ld c, a

	ld a, [hl]  ; OBJ_X
	sub a, 8        
	ld b, a
	call GetTile ; store tile data in hl
	ld a, [hl]
	call CompareAllTiles
	ret

; @param: hl: address of object
; @return: store data at tile address in reg a, also set compare flag to 0 if placed tile detected
CheckTileBelow:
	ld a, [hli] ; OBJ_Y
	sub a, 16 - 8
	ld c, a

	ld a, [hl]  ; OBJ_X
	sub a, 8        
	ld b, a
	call GetTile ; store tile data in hl
	ld a, [hl]
	call CompareAllTiles
	ret

; @param: hl: address of object
; @return: store data at tile address in reg a, also set z flag if empty tile detected
CheckTileLeft:
	ld a, [hli] ; OBJ_Y
	sub a, 16 + 0
	ld c, a

	ld a, [hl]  ; OBJ_X
	sub a, 8 + 8
	ld b, a
	call GetTile ; store tile addr in hl
	ld a, [hl]
	call CompareAllTiles ; z flag set if empty tile detected
	ret

; @param: hl: address of object
; @return: store data at tile address in reg a, also set compare flag to 0 if placed tile detected
CheckTileRight:
	ld a, [hli] ; OBJ_Y
	sub a, 16
	ld c, a

	ld a, [hl]  ; OBJ_X
	sub a, 8 - 8 ; unnecessary, but it's here to remind us that OAM_X offset is 8
	ld b, a
	call GetTile
	ld a, [hl]
	call CompareAllTiles
	ret

; Only call this after GetTile
; @param: before this function is called, the tile we are checking should have
; already been loaded into hl
; @return: set z flag if empty tile found
CompareAllTiles:
	ld a, [hl]
	cp EMPTY_TILE
	ret

; Store b = min_x, c = max_y (stores the grid position, not pixel position)
GetMinMaxX:
	ld a, [BOX1 + OAMA_X]
	ld b, a
	ld c, a
	ld a, [BOX2 + OAMA_X]
	cp b
	jp nc, .gminmaxx1
	; store min in b
	ld b, a
.gminmaxx1:
	cp c
	jp c, .gminmaxx2
	; store max in c
	ld c, a
.gminmaxx2:
	ld a, [BOX3 + OAMA_X]
	cp b
	jp nc, .gminmaxx3
	; store min in b
	ld b, a
.gminmaxx3
	cp c
	jp c, .gminmaxx4
	; store max in c
	ld c, a
.gminmaxx4
	ld a, [BOX4 + OAMA_X]
	cp b
	jp nc, .gminmaxx5
	; store min in b
	ld b, a
.gminmaxx5
	cp c
	jp c, .gminmaxx6
	; store max in c
	ld c, a
.gminmaxx6
	srl b ; b / 2
	srl b ; b / 4
	srl b ; b / 8
	srl c ; c / 2
	srl c ; c / 4
	srl c ; c / 8
	ret

; Store b = min_y, c = max_y (stores grid position, not pixel position)
GetMinMaxY:
	ld a, [BOX1 + OAMA_Y]
	ld b, a
	ld c, a

	ld a, [BOX2 + OAMA_Y]
	cp b
	jp nc, .gminmaxy1
	; store min in b
	ld b, a
.gminmaxy1:
	cp c
	jp c, .gminmaxy2
	; store max in c
	ld c, a
.gminmaxy2:
	ld a, [BOX3 + OAMA_Y]
	cp b
	jp nc, .gminmaxy3
	; store min in b
	ld b, a
.gminmaxy3
	cp c
	jp c, .gminmaxy4
	; store max in c
	ld c, a
.gminmaxy4
	ld a, [BOX4 + OAMA_X]
	cp b
	jp nc, .gminmaxy5
	; store min in b
	ld b, a
.gminmaxy5
	cp c
	jp c, .gminmaxy6
	; store max in c
	ld c, a
.gminmaxy6
	srl b ; b / 2
	srl b ; b / 4
	srl b ; b / 8
	srl c ; c / 2
	srl c ; c / 4
	srl c ; c / 8
	ret

