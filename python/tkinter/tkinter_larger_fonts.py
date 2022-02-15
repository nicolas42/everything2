# https://tkdocs.com/tutorial/firstexample.html

if __name__ == "__main__":
    # from tkinter import *
    import tkinter as tk 
    from tkinter import ttk
    from tkinter import font

    def calculate(*args):
        print(args)
        try:
            value = float(feet.get())
            meters.set(int(0.3048 * value * 10000.0 + 0.5)/10000.0)
        except ValueError:
            pass

    root = tk.Tk()
    root.title("OMG It's a Title")

    mainframe = ttk.Frame(root) # , padding="3 3 12 12")
    mainframe.grid_configure(padx=12, pady=12)
    mainframe.grid(column=0, row=0, sticky=(tk.N, tk.W, tk.E, tk.S))
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)

    feet = tk.StringVar()
    meters = tk.StringVar()

    # row 1
    ttk.Button(mainframe, text="OMG A Button", command=calculate).grid(column=1, row=1, sticky=tk.W)
    input_field = ttk.Entry(mainframe, width=7, textvariable=feet); input_field.grid(column=2, row=1, sticky=(tk.W, tk.E))
    ttk.Label(mainframe, text="feet").grid(column=3, row=1, sticky=tk.W)

    # row 2
    ttk.Label(mainframe, text="is equivalent to").grid(column=1, row=2, sticky=tk.E)
    ttk.Label(mainframe, textvariable=meters).grid(column=2, row=2, sticky=(tk.W, tk.E))
    ttk.Label(mainframe, text="meters").grid(column=3, row=2, sticky=tk.W)

    # row 3
    ttk.Button(mainframe, text="Calculate", command=calculate).grid(column=3, row=3, sticky=tk.W)

    # keyboard shortcuts
    input_field.bind("<Return>", calculate)
    root.bind("<Escape>", quit)

    # resize fonts
    for font_name in [ "TkDefaultFont", "TkTextFont", "TkFixedFont", "TkMenuFont", "TkHeadingFont", "TkCaptionFont", "TkSmallCaptionFont", "TkIconFont", "TkTooltipFont" ]:
        that_font = tk.font.nametofont(font_name)
        that_font.configure(size=20)

    # put padding around all elements
    for child in mainframe.winfo_children(): 
        child.grid_configure(padx=5, pady=5)


    input_field.focus()
    root.mainloop()
