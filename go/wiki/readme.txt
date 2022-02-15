Edit and saves html pages on a server.  

To view or edit the pages try something like this

localhost:8080/view/<page>
localhost:8080/edit/<page>

It uses HTML form post requests to save files on the server.
It's a small modification of https://github.com/benawad/gowiki

Apparently saving naked HTML is more insecure than saving text files though I struggle to think why.  Both could be made into 
executable files on the server and run through some other mechanism.  And javascript only runs client side.  I suppose node could 
used to run naked javascript on the server.  Oh yeah.  So there's that.  Stupid node.  

