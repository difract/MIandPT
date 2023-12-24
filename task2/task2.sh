#!/bin/bash 

source="https://spbu.ru/sveden/education"
destination="$PWD"
probe=false

dl_spbu_s_e ()  {
	curl "$source" -s --compressed -H -'User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:109.0) Gecko/20100101 Firefox/115.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8' -H 'Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3' -H 'Accept-Encoding: gzip, deflate, br' -H 'DNT: 1' -H 'Connection: keep-alive'
}

dl_spbu_oop ()
{
  if [ "$probe" = true ]; then
	    echo dl_spbu_s_e | grep -oP 'https://nc\.spbu\.ru/s/[^\s<>"'\'']+' | uniq | sort | head -n 10
	else
      echo dl_spbu_s_e | grep -oP 'https://nc\.spbu\.ru/s/[^\s<>"'\'']+' | uniq | sort
  fi
}

download ()
{
  url="$1"
  filename="${url//[^a-zA-Z0-9]/_}"
  filepath="$destination/$filename.zip"
	if ! wget wget -O "$filepath" "$1/download"; then
		>&2 echo "Cannot download $1"
		return 15
  fi
  echo "$filepath"
}

extract_zips() {
    file_path="$1"
    dest_dir="$2"

    unzip -o "$file_path" -d "$dest_dir"
    local result=$?
    if [ $result -ne 0 ]; then
        >&2 echo "Failed to extract $file_path"
    fi
    rm -f "$file_path"
}

recoll_indexing() {
    recollindex -r "$destination"
    local status=$?
    if [ $status -ne 0 ]; then
        >&2 echo "Indexing: failure"
        return $status
    else
        echo "Indexing: success"
    fi
}

#checking format

if ! OPTIONS=$(getopt -o s:d:p --long source:,destination:,probe -- "$@"); then
    echo "Wrong options format" >&2
    exit 1
fi

eval set -- "$OPTIONS"

#checking options

while true; do
    case "$1" in
    -s | --source)
        source="$2"
        shift 2
        ;;
    -d | --destination)
        destination="$2"
        shift 2
        ;;
    -p | --probe)
        probe=true
        shift
        ;;
    --)
        shift
        break
        ;;
    esac
done

#downloading and extracting

for u in $(dl_spbu_oop); do
	file=$(download "${u}")
	echo "Downloaded ${u}"
	extract_zips "$file" "$destination"
  echo $?
done

#indexing

recoll_indexing
status=$?
if [ $status -ne 0 ]; then
    exit $status
fi
