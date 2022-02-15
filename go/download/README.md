Concurrently download a bunch of files.  Edit the urls file then run 

    go run downloader.go

based on https://medium.com/@dhanushgopinath/concurrent-http-downloads-using-go-32fecfa1ed27

# How to get a bunch of image urls

Open a browser and make sure your adblocker is off.  Using privacy mode can sometimes be an easy way of disabling all extensions.

Go to google images and search for your image.  Scroll down to load as many images as you want. 

Open the console (ctrl+shift+j in chrome) and run the following code.  Make sure adblocker is off or be in privacy mode or some equivalent or the window won't open.

    urls = Array.from(document.querySelectorAll('.rg_di .rg_meta')).map(el=>JSON.parse(el.textContent).ou);
    window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));


# Download them quickly

Put your urls in urls.txt separated by newlines then run the code below or some equivalent 

    go run downloader.go

Images go to output directory
