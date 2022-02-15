// Show/Hide Reddit Sidebar



var show_hide_old_reddit_sidebar_n = 0;
function show_hide_old_reddit_sidebar(){

    var sidebar = document.querySelector('div.side');
    if ( show_hide_old_reddit_sidebar_n === 0 ) { 
        sidebar.style.display = 'block';	// sometimes style.display is not defined as something reasonable
        show_hide_old_reddit_sidebar_n += 1;
    }
    if (sidebar.style.display === 'block') {
        sidebar.style.display = 'none';
    } else if (sidebar.style.display === 'none') {
        sidebar.style.display = 'block';
    }
}

var show_hide_reddit_sidebar_n = 0;
function show_hide_reddit_sidebar(){

    var sidebar = document.querySelector("#SHORTCUT_FOCUSABLE_DIV > div:nth-child(4) > div > div > div > div._3ozFtOe6WpJEMUtxDOIvtU > div._31N0dvxfpsO6Ur5AKx4O5d > div._3Kd8DQpBIbsr5E1JcrMFTY._1tvThPWQpORoc2taKebHxs > div")
    if ( show_hide_reddit_sidebar_n === 0 ) { 
        sidebar.style.display = 'block';	// sometimes style.display is not defined as something reasonable
        show_hide_reddit_sidebar_n += 1;
    }

    if (sidebar.style.display === 'block') {
        sidebar.style.display = 'none';
    } else if (sidebar.style.display === 'none') {
        sidebar.style.display = 'block';
    }
}


show_hide_reddit_sidebar();
a = document.querySelector("#SHORTCUT_FOCUSABLE_DIV > div:nth-child(4) > div > div > div > div._3ozFtOe6WpJEMUtxDOIvtU > div._31N0dvxfpsO6Ur5AKx4O5d > div._1OVBBWLtHoSPfGCRaPzpTf._3nSp9cdBpqL13CqjdMr2L_._2OVNlZuUd8L9v0yVECZ2iA > div.rpBJOHq2PR60pnwJlUyP0")
a.style.width = '1000px'; // (window.innerWidth - 100).toString() + 'px'

