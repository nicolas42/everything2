rebol []

index-files: func [ d o /local f ] [ f: sort read d  foreach f f [ append o d/:f ]  foreach f f [ if equal? #"/" last f [ prin "." index-files d/:f o ] ]  return o ]

index-files %/Users/nick/Downloads/images/ o: []

remove-each o o [ not any [ suffix? o %.jpg  suffix? o %.png ] ]

list: func [ f ] [ foreach f f [ print f ] f ]

rotate: func [ blk ] [ 
    blk: next blk
    if tail? blk [ blk: head blk ]
    blk
]


resize-to-within: func [ a b ] [
    ; resize-to-within a: 12x9 b: 5x5

    is-within: func [ a b ] [ all [ a/x <= b/x  a/y <= b/y ] ]
    if is-within a b [ return a ]

    newa: as-pair (to-decimal a/x) * b/x / a/x   (to-decimal a/y) * b/x / a/x 
    if is-within newa b [ return newa ]

    newa: as-pair (to-decimal a/x) * b/y / a/y   (to-decimal a/y) * b/y / a/y 
    if is-within newa b [ return newa ]


]

version-that-resizes-window: [ 
    l: layout[
        origin 0x0 
        b: image "Load" [
            error? try [
                b/text: none
                b/image: i: load o/1
                o: rotate o
                new-size: probe resize-to-within i/size 1000x1000
                l/size: b/size: new-size
                show l
            ]
        ]
    ]
    view/options l [ resize ] 
]


l: layout[
    origin 0x0 
    backcolor black
    b: image 1000x1000 "Load" 
]

show-image-thing: func [ b o ] [ 
    b/image: i: load o/1
    new-size: probe resize-to-within i/size b/parent-face/size
    b/size: new-size
    b/text: none  
    show b
]

insert-event-func func [ f e ][
    ; keyboard migrates to next image
    ; clicking changing the directory
    if any [ e/type = 'key ] [
        error? try [
            o: rotate o
            show-image-thing b o 
        ]
    ]

    if e/type = 'down [ 
        error? try [
            f: first request-file 
            path: first split-path f
            index-files path o: copy []
            remove-each o o [ not any [ suffix? o %.jpg  suffix? o %.png ] ]
            o: find o f
            show-image-thing b o 




        ] 
    ]
    return e
]

view/options l [ resize ] 


view l: layout[origin 0x0 b: box "Load" [error? try [b/image: i: load first request-file b/text: "" l/size: b/size: i/size show l]]]

