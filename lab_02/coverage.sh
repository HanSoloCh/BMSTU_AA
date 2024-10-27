#!/bin/bash

LOG_FILE="out/test.log"

PREV_REPORT="cov/stud-unit-test-report-prev.json"
REPORT="cov/stud-unit-test-report.json"


./test.exe >> $LOG_FILE

files=

for file in $(find unit_tests -type f -name 'check_*.c' ! -name 'check_main.c'); do
	base_name=$(basename "$file" | sed 's/^check_//' | sed 's/\.c$//')
	if [ -f "src/$base_name.c" ] && [ "$base_name" != "main" ]; then
		files+="src/$base_name.c"
	fi
done

# Проверяем покрытие кода для каждого файла

coverage=0

for file in "${files[@]}"; do
  name="$(basename "$file")"
  gcov "$name" -o ./out -t > ./out/"$name.gcov"
  coverage=$(echo "$coverage + $(gcov "$name" -o ./out -n | tail -1 | sed "s/.*://g" | sed "s/%.*//g")" | bc)
done

if [[ ${#files[@]} -ne 0 ]]; then
  coverage=$(echo "scale=2; $coverage / ${#files[@]} / 100" | bc -l)
fi

if [ "$(echo "$coverage < 1" | bc)" -eq 1 ]; then
    coverage="0$coverage"
fi

# Результаты тестов
test_result=$(grep -E [0-9]*%: "$LOG_FILE")


# Получаем числа из строки
checks=$(echo "$test_result" | awk '{print $3}' | tr -d ',')
failures=$(echo "$test_result" | awk '{print $5}' | tr -d ',')
errors=$(echo "$test_result" | awk '{print $7}' | tr -d ',')


failed=$(($failures + $errors))
passed=$(($checks - $failed))


mkdir -p cov/

if [ -f "$REPORT" ]; then
    cp "$REPORT" "$PREV_REPORT"
fi

JSON_DATA="{
    \"timestamp\": \"$(date -u +"%Y-%m-%dT%H:%M:%S%z")\",
    \"coverage\": $coverage,
    \"passed\": $passed,
    \"failed\": $failed
}"

echo "$JSON_DATA" > "$REPORT"
