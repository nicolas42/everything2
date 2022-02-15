rebol []

find-any: func [ block string ] [
	foreach str block [
		if find string str [ return string ]
	]
	return none
]

find-all: func [ block string ] [
	foreach str block [
		if not find string str [ return none ]
	]
	return string
]


list: func [ files ] [
	i: 1
	foreach f files [
		prin i
		prin " "
		print f
		; print second split-path f 
		i: i + 1
	]
	return none
]

index-files: func [ dir out /local files ] [
	attempt [
	files: read dir
	
	foreach file files [
		append?: no
		if find-all yay dir/:file [ append?: yes ]
		if find-any nay dir/:file [ append?: no ]
		if append? [ append out dir/:file ]
	]
			
	; append out files

	foreach file files [ 
		if equal? #"/" last file [
			index-files dir/:file out
		]
	]
	]
	return out
]

wd: :what-dir

search: func [ dirs query ] [

	dirs: append copy [] dirs  ; convert single dir to block

	yay: copy [] 
	nay: copy []
	
	foreach word parse query none [
		either equal? #"-" first word [
			append nay remove word
		] [
			append yay word
		]
	]

	;yay: [ ".txt" ]
	;nay: [ ".c" ]

	files: copy []
	foreach dir dirs [
		index-files to-rebol-file dir files
	]
	return files
]

comment {
dirs: [ %/c/users/pc/Downloads/ %/c/users/pc/Documents/ ]
query: ".txt -.c"
search dirs query
}

list search dirs "PWM -Nucleo"

