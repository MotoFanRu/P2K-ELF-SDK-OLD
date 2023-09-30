/*
** UTF-8 w/o BOM
**
** DateBook
*/

#ifndef __SDK_DBK_H__
#define __SDK_DBK_H__

#include <typedefs.h>
#include <time_date.h>
#include <java.h>

/* result codes for DL_DBK_* functions */
enum
{
    DBK_RESULT_SUCCESS = 0,        // OK
    DBK_RESULT_IN_PROGRESS,        // OK, plz wait for event
    DBK_RESULT_HALTED,
    DBK_RESULT_INITIALIZING,
    DBK_RESULT_BUSY,            // FAIL, maybe later
    DBK_RESULT_LOCKED,
    DBK_RESULT_NOT_LOCKED,
    DBK_RESULT_OUT_OF_MEMORY,
    DBK_RESULT_LOCATIONS_UNAVAILABLE,
    DBK_RESULT_EVENT_TITLE_MISSING,
    DBK_RESULT_ALARM_FOLLOWS_EVENT,
    DBK_RESULT_INVALID_TIME_FORMAT,
    DBK_RESULT_INVALID_DATE_FORMAT,
    DBK_RESULT_INVALID_DURATION,
    DBK_RESULT_INVALID_SLOT_NUMBER,
    DBK_RESULT_SLOT_IS_EMPTY,
    DBK_RESULT_INVALID_PREFERENCE,
    DBK_RESULT_INVALID_ROUTE_ID,
    DBK_RESULT_INVALID_EVENT_ID,
    DBK_RESULT_INVALID_OBJECT_ID,
    DBK_RESULT_OBJECT_ID_IS_EMPTY,
    DBK_RESULT_FAILED_OBSOLETE
};
typedef UINT8 DBK_RESULT_T;


/* Event result codes. */
enum
{
    DBK_EVENT_RESULT_SUCCESS = 0,        // OK
    DBK_EVENT_RESULT_INVALID_ID,
    DBK_EVENT_RESULT_REPEAT_CHANGED,
    DBK_EVENT_RESULT_NO_LOCATION,
    DBK_EVENT_RESULT_NO_EVENT_FOUND,    // End
    DBK_EVENT_RESULT_NO_ALARM_FOUND,
    DBK_EVENT_RESULT_OVERLAP,
    DBK_EVENT_RESULT_NO_OVERLAP
};
typedef UINT8 DBK_EVENT_RESULT_T;


/* Repeating Event Type */
enum 
{
    DBK_REPEAT_NONE = 0,            // ���
    DBK_REPEAT_DAILY,                // ��������� 
    DBK_REPEAT_WEEKLY,                // �����������
    DBK_REPEAT_MONTHLY_ON_DATE,        // ������. �� ����
    DBK_REPEAT_MONTHLY_ON_DAY,        // ������. �� ���
    DBK_REPEAT_YEAR                    // ��������
};
typedef UINT8 DBK_REPEAT_TYPE_T;


/* Event change notification type. */
enum
{
    DBK_CHANGE_ADD_OR_UPDATE = 0,
    DBK_CHANGE_DELETE,
    DBK_CHANGE_SYNCHRONIZATION,
    DBK_CHANGE_ALARM,
    DBK_CHANGE_PREFERENCE
};
typedef UINT8 DBK_CHANGE_T;


#define DBK_EVENT_JAVA_NAME_LEN 32

#if defined(FTR_L7E) || defined(FTR_L9) || defined(L7e) || defined(L9)

typedef struct
{
    DBK_REPEAT_TYPE_T    type;
    union
    {
        struct
        {
            UINT16    interval;
        } daily;
        struct
        {
            UINT8    interval;
            UINT8    week_days:7;
        } weekly;
        struct
        {
            UINT8    interval;
            UINT8    specific_day:3;
            UINT8    day_of_week:3;
        } monthly;
        struct
        {
            UINT8    specific_day:3;
            UINT8    day_of_week:3;
        } yearly;
    } pattern;
    struct
    {
        UINT16        freq;
        CLK_DATE_T    end_date;
    } end_type;
} DBK_REPEAT_T;

#define DBK_EVENT_TITLE_LEN 128
#define DBK_EVENT_LOCATION_LEN 64
#define DBK_EVENT_NOTE_LEN 256

typedef struct
{
    WCHAR                title[DBK_EVENT_TITLE_LEN+1];    // ���������
    BOOL                timed_event;
    BOOL                alarm_enabled;    // ��������� ���/����
    CLK_TIME_T            start_time;        // ����� ������
    CLK_DATE_T            start_date;        // ���� ������ 
    CLK_TIME_T            end_time;        // ����� �����
    CLK_DATE_T            end_date;        // ���� ����� 
    UINT32                duration;        // �����������������
    CLK_TIME_T            alarm_time;        // ����� ����������
    CLK_DATE_T            alarm_date;        // ���� ����������
    DBK_REPEAT_T        repeat;            // ����� 
    UINT16                parent_id;
    BOOL                notes_truncated;
    BOOL                record_truncated;
    UINT8                category;
    WCHAR                location[DBK_EVENT_LOCATION_LEN+1];
    WCHAR                notes[DBK_EVENT_NOTE_LEN+1];
    UINT64                alarm_id;
    JAVA_APP_ID            java_id;        // id ��� ����������
    JAVA_APP_ID            java_suite_id; 
    WCHAR                java_name[DBK_EVENT_JAVA_NAME_LEN+1]; // ��� ���-����������
    UINT16                timezone;

} DBK_EVENT_DETAILS_T;

#else

typedef struct
{
    DBK_REPEAT_TYPE_T    type;
} DBK_REPEAT_T;

#define DBK_EVENT_TITLE_LEN 64

typedef struct
{
    WCHAR                title[DBK_EVENT_TITLE_LEN+1];    // ���������
    BOOL                timed_event;
    BOOL                alarm_enabled;    // ��������� ���/����
    CLK_TIME_T            start_time;        // ����� ������
    CLK_DATE_T            start_date;        // ���� ������ 
    UINT32                duration;        // �����������������
    CLK_TIME_T            alarm_time;        // ����� ����������
    CLK_DATE_T            alarm_date;        // ���� ����������
    DBK_REPEAT_T        repeat;            // ����� 
    JAVA_APP_ID            java_id;        // id ��� ����������
    JAVA_APP_ID            java_suite_id; 
    WCHAR                java_name[DBK_EVENT_JAVA_NAME_LEN+1]; // ��� ���-����������

} DBK_EVENT_DETAILS_T;

#endif

typedef struct
{
    CLK_CLOCK_T        alarm_time;
    CLK_CLOCK_T        event_start_time;
    CLK_CLOCK_T        timestamp;
    BOOL            is_timed_event;
    UINT16            slot_number;
} DBK_SORT_T;


/*  */
typedef struct
{
    UINT32                    event_id; //  ����� �������
    DBK_EVENT_DETAILS_T        event_details;
} DBK_EVENT_INSTANCE_T;


/*  */
typedef struct
{
    DBK_EVENT_RESULT_T        result;
    UINT16                    slot_number;
} DBK_ASYNC_OPERATION_T;


/* �������� � ������ ������ EV_DBK_ADD_EVENT */
typedef struct
{
    DBK_EVENT_RESULT_T        result;
    UINT32                    event_id;
} DL_DBK_ADD_EVENT_CNF_T;


/* �������� � ������ ������ EV_DBK_DATABASE_QUERY */
typedef struct
{
    DBK_EVENT_RESULT_T        result;
    DBK_EVENT_INSTANCE_T    event_instance;
} DBK_DATABASE_RESULT_T;


/* �������� � ������ ������ EV_DBK_DATABASE_ALTERED */
typedef struct
{
    DBK_CHANGE_T            type_of_change;
    UINT32                    event_id_mask;
    UINT32                    event_id_base;
} DBK_DATABASE_ALTERED_T;


/* �������� � ������ ������ EV_DBK_NUM_OF_EVENTS */
typedef struct
{
    DBK_EVENT_RESULT_T        result;
    UINT16                    number_of_events;
} DBK_NUMBER_OF_EVENTS_T;


/* �������� � ������ ������ EV_DBK_DATABASE_ALARM */
typedef struct
{
    DBK_EVENT_RESULT_T        result;
    DBK_SORT_T                alarm_info;
    UINT32                    event_id;
} DBK_DATABASE_ALARM_T;

// ����������� ���������� � ���� ������ ���������. ��� �������, ��� ��� ������ � ��������� ����� ������������������.
// ����� �������� �� 0x820E3 . �������� 
DBK_RESULT_T DL_DBK_RegisterApplication( SU_PORT_T su_port );

// �������� ��������
DBK_RESULT_T DL_DBK_UnregisterApplication( SU_PORT_T su_port );

DBK_RESULT_T DL_DBK_LockDatebookDatabase( SU_PORT_T su_port );
DBK_RESULT_T DL_DBK_UnLockDatebookDatabase( SU_PORT_T su_port );

DBK_RESULT_T DL_DBK_IsMemoryFull ( BOOL * dbk_memory_full );

// �������� �������, ����� ����� �� EV_DBK_ADD_EVENT
DBK_RESULT_T 
DL_DBK_AddEventToDatabase(        IFACE_DATA_T            *iface_data, 
                                DBK_EVENT_DETAILS_T        *event_details
                                ); 

// �������� ������� 
DBK_RESULT_T 
DL_DBK_UpdateEventData(            IFACE_DATA_T            *iface_data, 
                                DBK_EVENT_INSTANCE_T    *event_instance
                                );

// ������� �������
DBK_RESULT_T
DL_DBK_DeleteEventFromDatabase(        IFACE_DATA_T    *iface_data,
                                    UINT32            event_id,
                                    UINT8             extdelete // 0 - �����, 1 - ������ � ������� ������
                                    );

DBK_RESULT_T
DL_DBK_TestForEventOverlap(        IFACE_DATA_T            *iface_data,
                                DBK_EVENT_INSTANCE_T    *event_instance
                                );

// ����� ������ ������� � �������� ��������� ���� � �������. ����� ����� �� ������ EV_DBK_DATABASE_QUERY
DBK_RESULT_T 
DL_DBK_GetFirstEventInTimeFrame(    IFACE_DATA_T    *iface_data,
                                    CLK_DATE_T        start_date,
                                    CLK_TIME_T        start_time,
                                    CLK_DATE_T        end_date,
                                    CLK_TIME_T        end_time
                                    );

// ����� c�������� �������. ����� ����� �� ������ EV_DBK_DATABASE_QUERY
DBK_RESULT_T
DL_DBK_GetNextEventInTimeFrame(        IFACE_DATA_T    *iface_data,
                                    UINT32            event_id, // ����� ����������� ������� ?
                                    CLK_DATE_T        end_date,
                                    CLK_TIME_T        end_time);

// �������� ������� �� ��� ������. ����� ����� �� ������ EV_DBK_DATABASE_QUERY
DBK_RESULT_T 
DL_DBK_GetEventInstanceByIdNumber(    IFACE_DATA_T    *iface_data, 
                                    UINT32 event_id
                                    );

DBK_RESULT_T DL_DBK_GetMonthView(    IFACE_DATA_T    *iface_data,
                                    CLK_DATE_T        start_date,
                                    CLK_DATE_T        end_date 
                                );

DBK_RESULT_T DL_DBK_GetWeekView(    IFACE_DATA_T    *iface_data,
                                    CLK_DATE_T        start_date,
                                    CLK_DATE_T        end_date 
                                );

DBK_RESULT_T 
DL_DBK_GetNextEventForDayView(        IFACE_DATA_T    *iface_data,
                                    BOOL            first_event,
                                    CLK_DATE_T        day_to_view
                                    );

DBK_RESULT_T
DL_DBK_GetNextAlarm(        IFACE_DATA_T    *iface_data,
                            DBK_SORT_T        *prev_alarm_info_ptr 
                            );
#endif
