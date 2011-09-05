# sqlite2ical
sqlite2ical converts iPhone sqlite format calendars to iCal/vCal/ICS format. This is an Xcode project, but main.c could easily be compiled on Linux or other Unices. sqlite2ical depends on libical and libsqlite3.
Download a Mac binary of sqlite2ical here: http://cl.ly/1v1Q413G0Z3p3k0M0p08

As a bonus, this copy of sqlite2ical comes with a (Mach-O) precompiled copy of libical with i386 and ARM architectures (works perfectly for iPhone development).

## Usage
```sqlite2ical <input.sqlitedb> <output.ics>```

## Note
sqlite2ical will not currently convert recurring events. Feel free to fork the project and add it in if you'd like!

## License
sqlite2ical is intended for personal use. If you want to use it for anything else (i.e. in your own piece of software, etc.), let me know.

Copyright (c) 2011 Ari Weinstein/Squish Software<br>arixmail2 (at) gmail [DAWT] com
