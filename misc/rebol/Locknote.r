#!/usr/bin/env rebol 

REBOL []

locknote-ctx: make object! [
    request: func [text][
        layout1: layout [
            style h3 h3 font [name: "fixedsys" style: []] 
            style field field font [name: "fixedsys"] para [origin: 2x2] 
            style area area wrap white white edge [size: 0x0] font [name: "fixedsys"] 
            style link text font [size: 12 name: "fixedsys" color: blue style: []] edge [size: 0x0] 
            style field field white white edge [size: 0x0] 
            across origin 1 space 1 backcolor white 
            h3 (text) return 
            box silver 300x1 return 
            pad 120 
            link "Yes" 60 #"y" [result: yes hide-popup] 
            link "No" 60 #"n" [result: no hide-popup] 
            link "Cancel" 60 #"^[" [result: none hide-popup]
        ] 
        result: none 
        inform layout1 
        result
    ]
    request-text: func [
        "Requests a text string be entered." 
        /offset xy 
        /title title-text 
        /default str
    ][
        if none? str [str: copy ""] 
        text-lay: layout compose [
            across origin 1x1 space 1 backcolor white 
            style h3 h3 font [name: "fixedsys" style: []] 
            style field field font [name: "fixedsys"] para [origin: 2x2] 
            h3 (either title [title-text] ["Enter text below:"]) return 
            box silver 300x1 return 
            tf: field hide 300 str [ok: yes hide-popup] with [flags: [return]] return 
            box silver 300x1 return 
            pad 170 
            link "Enter" 60 [ok: yes hide-popup] 
            link "Cancel" 60 #"^[" [hide-popup]
        ] 
        ok: no 
        focus tf 
        either offset [inform/offset text-lay xy] [inform text-lay] 
        all [ok tf/data]
    ]
    crypt: func [
        "Encrypts or decrypts data and returns the result." 
        data [any-string!] "Data to encrypt or decrypt" 
        akey [binary!] "The encryption key" 
        /decrypt "Decrypt the data" 
        /binary "Produce binary decryption result." 
        /local port
    ][
        port: open [
            scheme: 'crypt 
            direction: pick [encrypt decrypt] not decrypt 
            key: akey 
            padding: true
        ] 
        insert port data 
        update port 
        data: copy port 
        close port 
        if all [decrypt not binary] [data: to-string data] 
        data
    ]
    encrypt: func [txt pass][
        join 
        checksum/secure txt 
        crypt txt checksum/secure pass
    ]
    decrypt: func [
        locknote pass 
        /local chk1 chk2 note
    ][
        chk1: copy/part locknote 20 
        note: crypt/decrypt skip locknote 20 checksum/secure pass 
        chk2: checksum/secure note 
        if equal? chk1 chk2 [note]
    ]
    locknote: #{
200D8019A7E0C8E17D83D2A1F420666CBD51E9A1F9891642F80D28F85CBD8AF3
F04D5641CB433321FF380BCEDFB95FDBFD68EF76D96923DEBF0C90C03371D106
4F2141820838A64B47FBE7E15E4FB50E70337321EFB743A1ECFCB5FB97DE0A4F
F4DB2C8DEF25D96587EE7B5EB14ACEEEDBC4030DDFE31D139561D87167D46BC0
77A6DCA7AA0DAB655EF99186
}
    save-locknote: func [file content][
        save/header file compose [
            locknote-ctx: (locknote-ctx) 
            locknote-ctx/view-locknote
        ] []
    ]
    view-locknote: func [][
        comment "secure [net ask file ask] " 
        stylize/master [
            area: area wrap white white edge [size: 0x0] font [name: "fixedsys"] 
            link: text font [size: 12 name: "fixedsys" color: blue style: []] edge [size: 0x0] 
            field: field white white edge [size: 0x0]
        ] 
        win: center-face layout [
            origin 1 space 1 backcolor white across 
            link "Set Password" [
                if not none? it: request-text/title "Enter new password" [
                    pass: it
                ]
            ] 
            return 
            hr: box 350x1 silver return 
            fac: area 350x350
        ] 
        insert-event-func func [face event /local file] [
            if event/type = 'close [
                if any [
                    old-pass <> pass 
                    original-text <> fac/text
                ] [
                    if request "Do you want to save the file?" [
                        file: any [rebol/options/script request-file/save/only] 
                        locknote: encrypt fac/text pass 
                        save-locknote file locknote
                    ]
                ]
            ] 
            if event/type = 'resize [
                hr/size/x: win/size/x - 2 
                fac/size: win/size - 0x25 
                fac/line-list: none 
                show fac 
                show hr
            ] 
            event
        ] 
        case [
            empty? locknote [
                pass: old-pass: copy "" 
                fac/text: copy "" 
                focus fac 
                view/title/options win "Lock Note" [resize]
            ] 
            not decrypt locknote "" [
                pass: old-pass: request-text/title "Please enter password" 
                if none? pass [pass: copy ""] 
                if fac/text: decrypt locknote pass [
                    original-text: copy fac/text 
                    focus fac 
                    view/title/options win "Lock Note" [resize]
                ]
            ] 
            decrypt locknote "" [
                pass: old-pass: copy "" 
                fac/text: decrypt locknote "" 
                original-text: copy fac/text 
                focus fac 
                view/title/options win "Lock Note" [resize]
            ]
        ]
    ]
] 
locknote-ctx/view-locknote