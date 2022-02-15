import numpy as np




def natural_sort_demo():

    print("\n")
    print("natural_sort_demo")
    print("---------------------")

    import natsort 
    a = ['Picture 13.jpg', 'Picture 14.jpg', 'Picture 15.jpg','Picture 0.jpg', 'Picture 1.jpg', 'Picture 10.jpg', 'Picture 11.jpg', 'Picture 12.jpg',  'Picture 16.jpg', 'Picture 17.jpg', 'Picture 18.jpg', 'Picture 19.jpg', 'Picture 2.jpg', 'Picture 20.jpg', 'Picture 21.jpg', 'Picture 22.jpg', 'Picture 23.jpg', 'Picture 24.jpg', 'Picture 25.jpg', 'Picture 26.jpg', 'Picture 27.jpg', 'Picture 28.jpg', 'Picture 29.jpg', 'Picture 3.jpg', 'Picture 30.jpg', 'Picture 31.jpg', 'Picture 32.jpg', 'Picture 33.jpg', 'Picture 34.jpg', 'Picture 35.jpg', 'Picture 36.jpg', 'Picture 37.jpg']         
    print(natsort.natsorted(a))





def blur(a):
    kernel = np.array([[1,1,1], [1,1,1], [1,1,1]])
    kernel = kernel / np.sum(kernel)
    arraylist = []
    for y in range(3):
        temparray = np.copy(a)
        temparray = np.roll(temparray, y - 1, axis=0)
        for x in range(3):
            temparray_X = np.copy(temparray)
            temparray_X = np.roll(temparray_X, x - 1, axis=1)*kernel[y,x]
            arraylist.append(temparray_X)

    arraylist = np.array(arraylist)
    arraylist_sum = np.sum(arraylist, axis=0)
    return arraylist_sum





def get_sign_of_multivector(_demo):

    def bubble_sort(arr):
        # using adjacent swaps
        # move the highest value to the nth place
        # then move the second highest value to the n-1th place
        # and so on.

        n = len(arr)
        for i in range(n-1):
            for j in range(0, n-i-1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    print(arr)

    def get_sign_of_multivector(arr):
        # every time a swap occurs between different elements
        # the sign is negated
        # this is consistent with anticommutativity

        n = len(arr)
        sign = 1
    
        for i in range(n-1):
            for j in range(0, n-1-i):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    sign = -sign
                    print(arr)
        
        print(sign, list(set(arr)))

    # demo 
    # in r3 there's one scalar and 3 vectors
    # vectors anticommute
    # 0 1 2 3
    # 0 1 2 3 12 23 31 123
    # 3221
    multivector_directions = [ [],[1],[2],[3],[1,2],[2,3],[3,1],[1,2,3]]
    arr = [3,1]
    print(arr)
    get_sign_of_multivector(arr)
 


    
def matplotlib_draw_circle_demo():

    # pip3 install matplotlib
    import matplotlib.pyplot as plt
    import math

    def approximate_circle(n = 10):
        X,Y = [], []
        for i in range(n+1):
            theta = i * 2 * math.pi / n
            X.append( math.cos(theta) )
            Y.append( math.sin(theta) )
        return X,Y

    def approximate_circle_with_derivative(n = 10):
        dt = 2 * math.pi / n
        X,Y = [], []
        x,y,t = 1,0-dt/2,0,
        X.append(x); Y.append(y)

        for i in range(n):

            x = x - math.sin(t)*dt
            y = y + math.cos(t)*dt
            t = t + dt
            
            X.append(x)
            Y.append(y)
        return X,Y

    # demo
    plt.plot(*approximate_circle(n=20), color = 'blue')
    plt.plot(*approximate_circle_with_derivative(n=20), color='red')
    plt.ylabel('some numbers')
    plt.show()






from typing import NamedTuple

def named_tuple_demo():
    class SomeType(NamedTuple):
        x: int
        y: int 
        data: bytes
        z: int = 4 

    a = SomeType(1, 2, bytes([12,31,23,123,1]) )

    print(a)





import math
import numpy as np


def newtons_method(f, dfdx):

    # Newton's method approximates solutions to equations by successive calculation of 
    # tangent lines. It requires an initial starting point.  Different starting points 
    # will yield different solutions. 

    # An arbitrary tangent line of a curve that goes through point (x0,y0) can be 
    # formulated as y-y0 = m(x-x0).  The x-intercept of this line is (-y0 / m + x0)

    equality_distance = 1e-10 # float equality is defined as being closer than this
    decimal_places = 5 # needs to be low enough to prevent duplicate solutions

    solutions = set()
    for x in np.arange(-100,100, 0.1):
        while True:
            y = f(x)
            dydx = dfdx(x)
            x_next = -y / dydx + x 
            if abs(x_next - x) < equality_distance:
                break
            x = x_next
        solutions.add(round(x, decimal_places))
    
    return sorted(solutions)
    print(solutions)

def newtons_method_demo():
    f = lambda x : 1 -23*x + 12*x**2 + 213*x**3
    dfdx = lambda x : -23 + 24*x + 213*3*x**2
    solutions = newtons_method(f, dfdx)
    print(solutions)





def print_on_one_line_demo():
    # Printing a carriage return \r character moves the caret to the beginning of the line
    # Printing a newline character \n moves the caret to the next line.
    # To print on one line simply print a carriage return prior to the line
    # This will overwrite the current line if it is not empty

    import time
    import sys

    for i in range(100):
        time.sleep(0.001)
        print('\rDownloading File FooFile.txt [%d%%]' % i, end="")
        sys.stdout.flush()
    print("")



import os 

def pwd(): 
    return os.getcwd()

def ls():
    return os.listdir()

def cd(a):
    return os.chdir(a)

# def read(filename):
#     f = open(filename, "rb")
#     d=f.read()
#     f.close()
#     return d


# os.getenv("PATH")

def to_string(bytes_data):
    # works on improperly encoded data
    return ''.join(map(chr,bytes_data))



def find_prime_factors(n):
    i = 2
    factors = []
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors

def find_prime_factors_demo():
    for n in [ 2009, 720720, 999983 ]:
        s=str(n)+" = 1"
        for p in find_prime_factors(n):
            s=s+" * "+str(p)
        print(s)




import math


def find_roots_with_newtons_method(f, fdash, x0):
    while True:
        y0 = f(x0)
        m = fdash(x0)
        x_intercept = -y0 / m + x0
        if (abs(x_intercept - x0) < 1e-10):
            return x_intercept
        else:
            x0 = x_intercept
    


def find_roots(f, fdash, xs):
    roots = set()
    for x in xs:
        try:
            r = find_roots_with_newtons_method(f, fdash, x)
            r = round(r, 7)
            roots.add(r)
        except Exception as e:
            print(e)
    roots = list(roots)
    roots.sort()
    return roots


def find_roots_demo():
    def f(x): return (2+x-x**2)
    def fdash(x): return 1-2*x
    r = find_roots(f, fdash, range(-100, 100))
    print(r)







import random
import math

def estimate_pi_with_monte_carlo():

    random.seed()

    inside_circle = 0
    inside_square = 0

    for inside_square in range(1000000):
        x = random.random()
        y = random.random()
        # if math.sqrt(x**2 + y**2) <= 1:
        if x*x + y*y <= 1:
            inside_circle += 1

    # # inside_circle should be proportional to the area of a circle
    # # inside_square should be proportional to the area of a square
    # pi r^2
    # 4r^2

    pi_estimation = inside_circle / inside_square * 4

    print(pi_estimation)

    








# https://docs.python.org/3/library/re.html

import re
import sys

def bash_grep(filename, expression):
    f = open(filename)
    text = f.read()
    f.close()

    out=[]
    for line in text.split("\n"):
        matches = re.search(expression, line)
        if matches: 
            out.append(matches[0])

    return out 


def bash_grep_demo():

    print("\n")
    print("bash_grep_demo")
    print("---------------------")

    # get all function lines
    filename   = "misc.py"
    expression = "def .*?\(.*?\):"
    matches = bash_grep(filename, expression)
    for match in matches: print(match)







import os
import sys

def find_case_insensitive(a,b):
    # return index or -1 if not found
	return a.lower().find(b.lower())


def find_files( top_dir, query ):

    # usage: find_files(".", "key words separated by whitespace")

    query = query.split() # split at whitespace

    for root, dirs, files in os.walk(top_dir):
        # print(root,dirs,files)

        for dir in dirs:
            files.append(dir)

        for file in files:
            full_path = os.path.join(root, file)
            was_found = True	
            for query_word in query:
                if -1 == find_case_insensitive(full_path, query_word):
                    was_found = False
            if was_found:
                print(full_path)



def find_files_demo():

    print("\n")
    print("find_files_demo")
    print("---------------------")

    for ext in [ ".txt" ]: # , ".py", ".c", ".md", ".jpg", ".png" ]:
        find_files( "..", ext )


def find_files_terminal():
    import pathlib 

    if ( len(sys.argv) < 2 ):
        print("usage: python find_files.py dir query")
        exit()


    query = [""]
    top_dir = os.getcwd()

    script_name = sys.argv[0]
    top_dir = sys.argv[1]
    query = sys.argv[2:]
    if ( top_dir == "." ): top_dir = os.getcwd()
    if ( top_dir == "~" ): top_dir = pathlib.Path.home()
    
    print(script_name, top_dir, query, "\n")
    find_files( top_dir, query )







def vigenere_cipher(plaintext, key):

    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    table = [
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "BCDEFGHIJKLMNOPQRSTUVWXYZA",
    "CDEFGHIJKLMNOPQRSTUVWXYZAB",
    "DEFGHIJKLMNOPQRSTUVWXYZABC",
    "EFGHIJKLMNOPQRSTUVWXYZABCD",
    "FGHIJKLMNOPQRSTUVWXYZABCDE",
    "GHIJKLMNOPQRSTUVWXYZABCDEF",
    "HIJKLMNOPQRSTUVWXYZABCDEFG",
    "IJKLMNOPQRSTUVWXYZABCDEFGH",
    "JKLMNOPQRSTUVWXYZABCDEFGHI",
    "KLMNOPQRSTUVWXYZABCDEFGHIJ",
    "LMNOPQRSTUVWXYZABCDEFGHIJK",
    "MNOPQRSTUVWXYZABCDEFGHIJKL",
    "NOPQRSTUVWXYZABCDEFGHIJKLM",
    "OPQRSTUVWXYZABCDEFGHIJKLMN",
    "PQRSTUVWXYZABCDEFGHIJKLMNO",
    "QRSTUVWXYZABCDEFGHIJKLMNOP",
    "RSTUVWXYZABCDEFGHIJKLMNOPQ",
    "STUVWXYZABCDEFGHIJKLMNOPQR",
    "TUVWXYZABCDEFGHIJKLMNOPQRS",
    "UVWXYZABCDEFGHIJKLMNOPQRST",
    "VWXYZABCDEFGHIJKLMNOPQRSTU",
    "WXYZABCDEFGHIJKLMNOPQRSTUV",
    "XYZABCDEFGHIJKLMNOPQRSTUVW",
    "YZABCDEFGHIJKLMNOPQRSTUVWX",
    "ZABCDEFGHIJKLMNOPQRSTUVWXY",]

    repeated_key = key
    while len(repeated_key) < len(plaintext):
        repeated_key += key # concatenate

    ciphertext = ""
    for i,_ in enumerate(plaintext):
        y = ord(plaintext[i].upper())-65
        x = ord(repeated_key[i].upper())-65
        ciphertext += table[y][x]

    return ciphertext


def vigenere_cipher_demo():


    print("\n")
    print("vigenere_cipher_demo")
    print("---------------------")

    # test
    plaintext = "attackatdawn"
    key = "LEMON"
    ciphertext = vigenere_cipher(plaintext, key)
    if ciphertext != "LXFOPVEFRNHR":
        print("ERROR")
    
    print(ciphertext)






# def wget_unverified(url):

#     # curcumvents certificate errors O_o
#     # Install certificate instead

#     import wget
#     import sys
#     import ssl

#     ssl._create_default_https_context = ssl._create_unverified_context
#     wget.download(url)





# Download files in parallel
# ------------------------------
# doesn't work if pasted into python shell

import multiprocessing
import wget
import os

# Circumvent SSL: CERTIFICATE_VERIFY_FAILED errors
# https://stackoverflow.com/questions/50236117/scraping-ssl-certificate-verify-failed-error-for-http-en-wikipedia-org
import ssl
ssl._create_default_https_context = ssl._create_unverified_context

# How to get image urls from google images
# ------------------------------
# Search google images and use the following javascript
# urls = Array.from(document.querySelectorAll('.rg_di .rg_meta')).map(el=>JSON.parse(el.textContent).ou);
# window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));


def wget_process(args):
    url = args[0]
    output_dir = args[1]
    try:
        wget.download(url, out=output_dir, bar=None)
        return ('Downloaded', url)
    except Exception as e:
        return (str(e), url )

def parallel_wget_demo():

    print("\n")
    print("parallel_wget_demo")
    print("---------------------")

    output_dir = "Downloads_gitignore"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    args = [
        [ "https://upload.wikimedia.org/wikipedia/commons/4/4b/Ursidae-01.jpg" , output_dir ], 
        [ "https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/2010-kodiak-bear-1.jpg/1200px-2010-kodiak-bear-1.jpg" , output_dir ], 
        [ "https://media.4-paws.org/8/a/a/0/8aa007ca1ea6b56e152eaa378cac580af6fcbdc1/YAR_6487-5272x3648.jpg" , output_dir ], 
        [ "https://image.pbs.org/video-assets/ae5wgeQ-asset-mezzanine-16x9-MqD4B29.jpg" , output_dir ], 
        [ "https://www.sciencenewsforstudents.org/wp-content/uploads/2021/04/1440_bb_brown_black_bear_explainer_feat-1030x580.jpg" , output_dir ], 
    ]

    with multiprocessing.Pool(10) as pool:
        # imap_unordered allows for results to be returned in the order in which they are generated
        for result in pool.imap_unordered(wget_process, args):
            print(' '.join(result))




def matplotlib_pareto_demo():

    print("\n")
    print("matplotlib_pareto_demo")
    print("---------------------")

    # Income is normally distributed and proportional to current wealth

    import random
    import numpy as np 
    import matplotlib.pyplot as plt
    from matplotlib.animation import FuncAnimation

    fig, subplot = plt.subplots(nrows = 1, ncols = 1, figsize = (15,5))
    plt.style.use("ggplot")

    n = 400
    basic_income = 0

    x1 = [ x for x in range(0,n+1) ]
    y1 = [ 1 for y in range(0,n+1) ]


    def animate( i ):
        nonlocal x1, y1

        if i == 0:
            subplot.plot(x1,y1)
            return

        subplot.cla() # clear figure but not axes
        y1 = [ y + np.random.normal(0, y/10) + basic_income for y in y1 ] 
        y1.sort(reverse = True)

        subplot.set_xlim(0, n)
        subplot.set_ylim(0, np.amax(y1))
        subplot.set_title("Pareto distribution from stochastic process " + str(i))

        subplot.plot(x1,y1)
        
    anim = FuncAnimation(fig, animate, interval=100)
    plt.show()





from sdl2 import *
import ctypes
import numpy as np

def sdl_pareto_demo():
    window_width = 800
    window_height = 600
    SDL_Init(SDL_INIT_VIDEO)
    window = SDL_CreateWindow(b"SDL Pareto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN)
    renderer = SDL_CreateRenderer(window, -1, 0)

    SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255)
    SDL_RenderClear(renderer)
    SDL_SetRenderDrawColor(renderer, 0,0,0,255)
    SDL_RenderDrawLine(renderer, 100,100,200,200)
    SDL_RenderPresent(renderer)

    xscale = 1
    yscale = window_height
    x1 = [ x for x in range(0,window_width) ]
    y1 = [ 1 for y in range(0,window_width) ]

    running = True
    event = SDL_Event()
    while running:
        while SDL_PollEvent(ctypes.byref(event)) != 0:
            if event.type == SDL_QUIT:
                running = False
                break

        # calculate updated values
        y1 = [ y + np.random.normal(0, y/10) for y in y1 ] 
        y1 = [ y / np.amax(y1) for y in y1 ]  # normalize

        y1.sort(reverse = True)
        # print(y1)

        # render with scaling
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)
        SDL_RenderClear(renderer)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)
        for i in range(1, len(y1)):
            SDL_RenderDrawLine(renderer, 
                int(x1[i-1] * xscale), 
                int( window_height - (y1[i-1] * yscale) ), 
                int(x1[i] * xscale), 
                int( window_height - (y1[i] * yscale) ) 
            )

        SDL_RenderPresent(renderer)
        SDL_Delay(100)


    SDL_DestroyWindow(window)
    SDL_Quit()
    return 0








import os 
import os.path

def index_files( dir, out ):
    # alternative to os.walk, recursive

    files = os.listdir(dir)

    for file in files: 
        out.append( os.sep.join([ dir, file ]) )

    for file in files:
        full_path = os.sep.join([dir, file])
        if os.path.isdir(full_path):
            # print(full_path)
            index_files( full_path, out )

    return out 


def index_files_demo():

    print("\n")
    print("index_files_demo")
    print("---------------------")

    out = []
    dir = os.path.realpath("..")
    index_files(dir, out)
    for i in out[:10]: 
        print(i)






import os 
import os.path
import re
import sys

def print_columns(row, column_size = 40):

    for elem in row:

        column = ""
        column += str(elem)
        while len(column) < column_size:
            column = " " + column 

        print( "{",column,"}", end="")

    print("")


def print_columns_demo():

    print("\n")
    print("print_columns_demo")
    print("---------------------")

    for filename in os.listdir():
        m = re.search("(.*?)(\.py)", filename)
        if m: 
            # print(m.groups(), m.lastindex)
            # for i in range(1, m.lastindex+1):
            #     print(m[i])
            print_columns([filename, m[1]+".txt"], column_size = 50)









import re
import sys

def read_file(filename):
    file = open(filename,'r')
    input_string = file.read()
    file.close()
    return input_string



def demo_split_at_regex():
    filename = "misc.py"
    output_filename = 'output.txt'
    regex_pattern = r'\nFPS:\d*\.\d*\s*AVG_FPS:\d*\.\d*\n\n\s*cvWriteFrame\s*\nObjects:\s*\n'

    input_string = read_file(filename)
    output_list = re.split(regex_pattern, input_string)

    # print items in output_list
    for _,v in enumerate(output_list):
        print('{' + v + '}')






import random
import requests
import os


def read_thru(url):
    # read a url or its locally cached file

    cached_file = url.split('//')[-1].replace('/','-')

    if os.path.exists(cached_file):
        f = open(cached_file,'r')
        data = f.read()
        f.close()
        return data

    # download url
    print('\nreading', url, '...\n')
    response = requests.get(url)
    response.encoding = 'utf-8'
    data = response.text
    f = open(cached_file,'w')
    f.write(data)
    f.close()
    return data


def make_story_with_markov_chain(data):
    output = []
    data = data.split() # split at whitespace

    position = random.randint(0, len(data)-3) # 24158 

    output.append(data[position])
    output.append(data[position+1])

    for j in range(100):
        # print(j)
        locations_of_matches = []
        for i,_ in enumerate(data):
            if data[i].lower() == output[-2].lower() and data[i+1].lower() == output[-1].lower():
                # print(i)
                locations_of_matches.append(i)

        # print(locations_of_matches)        
        # for l in locations_of_matches:
        #     print(data[l], data[l+1], data[l+2])
        random_match_location = random.choice(locations_of_matches)
        new_word = data[random_match_location+2]
        output.append(new_word)
        print(new_word, end=' ', flush=True)

    print()
    # joined_result = ' '.join(output)
    # print(joined_result)


def make_story_with_markov_chain_demo():

    print("\n")
    print("make_story_with_markov_chain_demo")
    print("---------------------")

    # download moby dick
    # url = 'https://www.gutenberg.org/files/2701/2701-0.txt'
    url = 'https://nschmidt-public.s3.ap-southeast-2.amazonaws.com/2701-0.txt' # mirror
    text = read_thru(url)
    make_story_with_markov_chain(text)


def ordered_datetime():
    import datetime
    return datetime.datetime.now().strftime("%Y%m%d_%H%M%S")

def ordered_datetime_demo():
    print("\n")
    print("ordered_datetime_demo")
    print("---------------------")
    ordered_datetime()




from multiprocessing import Process

import kmeans_clustering_algorithm 
# kmeans_clustering_algorithm.demo

def dont_deserve_their_own_process():
    get_sign_of_multivector_demo()
    named_tuple_demo()
    newtons_method_demo()
    print_on_one_line_demo()
    natural_sort_demo()
    bash_grep_demo()
    find_files_demo()
    vigenere_cipher_demo()
    index_files_demo()
    print_columns_demo()
    ordered_datetime_demo()
    demo_split_at_regex()

if __name__ == "__main__":

    processes = []
    for f in [ 
        dont_deserve_their_own_process, 
        matplotlib_draw_circle_demo,  
        parallel_wget_demo, 
        matplotlib_pareto_demo, 
        sdl_pareto_demo, 
        make_story_with_markov_chain_demo 
    ]:
        p = Process(target=f)
        processes.append(p)
        p.start()

    for p in processes:
        p.join()


