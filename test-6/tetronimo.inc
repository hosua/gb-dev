; Initialize the object
InitOrigin:
	ld a, ORIGIN_START_X
	ld [originX], a
	ld a, ORIGIN_START_Y
	ld [originY], a
	ret

InitBoxes:
	ld a, 0
	ld [BOX1 + OAMA_Y], a     ; Store the object's Y value
	ld [BOX1 + OAMA_X], a     ; Store the object's X value
	ld [BOX1 + OAMA_FLAGS], a ; Set Object's Attributes to 0
	ld a, BOX_OBJ_TILE
	ld [BOX1 + OAMA_TILEID], a ; Set Object's Tile ID to 0

	ld [BOX2 + OAMA_Y], a     ; Store the object's Y value
	ld [BOX2 + OAMA_X], a     ; Store the object's X value
	ld [BOX2 + OAMA_FLAGS], a ; Set Object's Attributes to 0
	ld a, BOX_OBJ_TILE
	ld [BOX2 + OAMA_TILEID], a ; Set Object's Tile ID to 0

	ld [BOX3 + OAMA_Y], a     ; Store the object's Y value
	ld [BOX3 + OAMA_X], a     ; Store the object's X value
	ld [BOX3 + OAMA_FLAGS], a ; Set Object's Attributes to 0
	ld a, BOX_OBJ_TILE
	ld [BOX3 + OAMA_TILEID], a ; Set Object's Tile ID to 0

	ld [BOX4 + OAMA_Y], a     ; Store the object's Y value
	ld [BOX4 + OAMA_X], a     ; Store the object's X value
	ld [BOX4 + OAMA_FLAGS], a ; Set Object's Attributes to 0
	ld a, BOX_OBJ_TILE
	ld [BOX4 + OAMA_TILEID], a ; Set Object's Tile ID to 0
	ret

; Calculate box positions for O piece
CalcPos_O:
	; BOX 1
	ld a, [originY]
	ld [BOX1 + OAMA_Y], a     ; Store the object's Y value
	ld a, [originX]
	ld [BOX1 + OAMA_X], a     ; Store the object's X value
	ld a, BOX_OBJ_TILE
	ld [BOX1 + OAMA_TILEID], a ; Set Object's Tile ID to 0
	ld a, 0		   
	ld [BOX1 + OAMA_FLAGS], a ; Set Object's Attributes to 0
	
	; BOX 2
	ld a, [originY]
	ld [BOX2 + OAMA_Y], a      ; Store the object's Y value
	ld a, [originX] 		   
	add a, 8
	ld [BOX2 + OAMA_X], a      ; Store the object's X value
	ld a, BOX_OBJ_TILE
	ld [BOX2 + OAMA_TILEID], a ; Set Object's Tile ID to 0
	ld a, 0		               
	ld [BOX2 + OAMA_FLAGS], a  ; Set Object's Attributes to 0
	
	; BOX 3
	ld a, [originY]
	add a, 8
	ld [BOX3 + OAMA_Y], a      ; Store the object's Y value
	ld a, [originX]
	ld [BOX3 + OAMA_X], a      ; Store the object's X value
	ld a, BOX_OBJ_TILE
	ld [BOX3 + OAMA_TILEID], a ; Set Object's Tile ID to 0
	ld a, 0		               
	ld [BOX3 + OAMA_FLAGS], a  ; Set Object's Attributes to 0

	ld a, [originY]
	add a, 8
	ld [BOX4 + OAMA_Y], a      ; Store the object's Y value
	ld a, [originX]
	add a, 8
	ld [BOX4 + OAMA_X], a      ; Store the object's X value
	ld a, BOX_OBJ_TILE
	ld [BOX4 + OAMA_TILEID], a ; Set Object's Tile ID to 0
	ld a, 0		   
	ld [BOX4 + OAMA_FLAGS], a  ; Set Object's Attributes to 0
	ret
