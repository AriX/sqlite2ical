#include <CoreFoundation/CoreFoundation.h>
#include <libical/ical.h>
#include <sqlite3.h>

int main (int argc, const char * argv[]) {
	if (argc > 2) {
		// Initialize new calendar
		icalcomponent *calendar = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);	
		
		sqlite3 *database;
		sqlite3_stmt *statement;
		char *sql;
		int row = 0;
		
		// Open database and select all from events
		sqlite3_open(argv[1], &database);
		sql = "SELECT summary, description, start_date, end_date, start_tz, url, location FROM Event";
		sqlite3_prepare_v2(database, sql, strlen(sql)+1, &statement, NULL);
		
		while (1) {
			int s;
			
			// Step through each event
			s = sqlite3_step(statement);
			if (s == SQLITE_ROW) {
				// Assemble an ical event from each entry - this implementation only supports name, description, start date, end date, time zone, URL, and location, but it would be easy to add more
				icalcomponent *event = icalcomponent_new(ICAL_VEVENT_COMPONENT);
				icalproperty *nameProperty = icalproperty_new_summary((const char *)sqlite3_column_text(statement, 0));
				icalproperty *descriptionProperty = icalproperty_new_description((const char *)sqlite3_column_text(statement, 1));
				icalproperty *startDate = icalproperty_new_dtstart(icaltime_from_timet(978292800+atoi((const char *)sqlite3_column_text(statement, 2)), 0));
				icalproperty *endDate = icalproperty_new_dtend(icaltime_from_timet(978292800+atoi((const char *)sqlite3_column_text(statement, 3)), 0));
				icalproperty *timezoneProperty = icalproperty_new_tzid((const char *)sqlite3_column_text(statement, 4));
				icalproperty *URLProperty = icalproperty_new_url((const char *)sqlite3_column_text(statement, 5));
				icalproperty *locationProperty = icalproperty_new_location((const char *)sqlite3_column_text(statement, 6));
				icalcomponent_add_property(event, nameProperty);
				icalcomponent_add_property(event, descriptionProperty);
				icalcomponent_add_property(event, startDate);
				icalcomponent_add_property(event, endDate);
				icalcomponent_add_property(event, timezoneProperty);
				icalcomponent_add_property(event, URLProperty);
				icalcomponent_add_property(event, locationProperty);
				
				// Add ical event to calendar
				icalcomponent_add_component(calendar, event);
				row++;
			}
			else if (s == SQLITE_DONE) {
				printf("Finished reading sqlite database.\n");
				break;
			}
			else {
				fprintf(stderr, "Failed to open sqlite database.\n");
				exit(1);
			}
		}
		// Write ical calendar to file
		FILE *file = fopen(argv[2], "w");
		if (file == NULL) {
			fprintf(stderr, "Failed to open output file.\n");
		} else {
			fprintf(file, "%s", icalcomponent_as_ical_string(calendar));
			fclose(file);
			printf("Successfully wrote ical calendar!\n");
		}		
		return 0; 
	} else if (argc == 1 || (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')) {
		printf("sqlite2ical converts iPhone sqlite format calendars to iCal/vCal/ICS format\n\nsqlite2ical <input.sqlitedb> <output.ics>\n\nCopyright (c) 2011 Ari Weinstein/Squish Software\n");
	} else {
		printf("sqlite2ical\n\nIncorrect arguments. Try sqlite2ical -h.\n\nCopyright (c) 2011 Ari Weinstein/Squish Software\n");
	}
    return 0;
}
