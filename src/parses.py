from datetime import datetime
import dateparser
from zoneinfo import ZoneInfo


NY = ZoneInfo("America/New_York")

def parse_user_datetime_dateparser(text: str, tz="America/New_York") -> datetime:
    dt = dateparser.parse(
        text,
        settings={
            "TIMEZONE": tz,
            "RETURN_AS_TIMEZONE_AWARE": True,
            "PREFER_DATES_FROM": "future",
            "RELATIVE_BASE": datetime.now(NY),   
        }
    )

    if dt is None:
        raise ValueError(f"Could not parse date/time from: {text!r}")

    # Normalize to New York time
    dt = dt.astimezone(NY)

    return dt


def epoch(dt: datetime) -> int:
    return int (dt.timestamp())

def normalise(dt: datetime) -> str:
    return dt.isoformat()

def main():
    for i in range(3):
        ape = input("input date in different formats\n");
        date = parse_user_datetime_dateparser(ape);
        print(normalise(date))
        print(epoch(date))
        
main()