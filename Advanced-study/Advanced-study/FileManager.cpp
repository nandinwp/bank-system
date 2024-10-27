// FileManager.cpp
#include "FileManager.h"

IniFile* FileManager::load_ini(const char* filename)
{
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) return NULL;

    IniFile* ini = (IniFile*)malloc(sizeof(IniFile));
    ini->sections = NULL;
    ini->section_count = 0;

    char line[MAX_LINE];
    IniSection* current_section = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == ';' || line[0] == '\n') continue;

        if (line[0] == '[') {
            ini->section_count++;
            ini->sections = (IniSection*)realloc(ini->sections, sizeof(IniSection) * ini->section_count);
            current_section = &ini->sections[ini->section_count - 1];
            current_section->pair_count = 0;
            current_section->pairs = NULL;

            if (sscanf_s(line, "[%63[^]]]", current_section->section, (unsigned)_countof(current_section->section)) == 1) {

            }
            else {

            }
        }
        else if (current_section) {
            IniPair pair;

            if (sscanf_s(line, "%63[^=]=%255[^\n]", pair.key, (unsigned)_countof(pair.key), pair.value, (unsigned)_countof(pair.value)) == 2) {

                current_section->pair_count++;
                IniPair* new_pairs = (IniPair*)realloc(current_section->pairs, sizeof(IniPair) * current_section->pair_count);
                if (new_pairs == NULL) {
                    fclose(file);
                    free_ini(ini);
                    return NULL;
                }
                current_section->pairs = new_pairs;
                current_section->pairs[current_section->pair_count - 1] = pair;
            }
            else 
            {

            }
        }
    }

    fclose(file);
    return ini;
}



const char* FileManager::get_value(IniFile* ini, const char* section, const char* key) {
    for (int i = 0; i < ini->section_count; i++) {
        if (strcmp(ini->sections[i].section, section) == 0) {
            for (int j = 0; j < ini->sections[i].pair_count; j++) {
                if (strcmp(ini->sections[i].pairs[j].key, key) == 0) {
                    return ini->sections[i].pairs[j].value;
                }
            }
        }
    }
    return NULL;
}


void FileManager::set_value(IniFile* ini, const char* section, const char* key, const char* value) {
    for (int i = 0; i < ini->section_count; i++) {
        if (strcmp(ini->sections[i].section, section) == 0) {
            for (int j = 0; j < ini->sections[i].pair_count; j++) {
                if (strcmp(ini->sections[i].pairs[j].key, key) == 0) {
                    strncpy_s(ini->sections[i].pairs[j].value, value, MAX_VALUE);
                    return;
                }
            }
            ini->sections[i].pair_count++;
            ini->sections[i].pairs = (IniPair*)realloc(ini->sections[i].pairs, sizeof(IniPair) * ini->sections[i].pair_count);
            strncpy_s(ini->sections[i].pairs[ini->sections[i].pair_count - 1].key, key, MAX_KEY);
            strncpy_s(ini->sections[i].pairs[ini->sections[i].pair_count - 1].value, value, MAX_VALUE);
            return;
        }
    }

    ini->section_count++;
    ini->sections = (IniSection*)realloc(ini->sections, sizeof(IniSection) * ini->section_count);
    IniSection* new_section = &ini->sections[ini->section_count - 1];
    strncpy_s(new_section->section, section, MAX_SECTION);
    new_section->pair_count = 1;
    new_section->pairs = (IniPair*)malloc(sizeof(IniPair));
    strncpy_s(new_section->pairs[0].key, key, MAX_KEY);
    strncpy_s(new_section->pairs[0].value, value, MAX_VALUE);
}


void FileManager::save_ini(const IniFile* ini, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) return;

    for (int i = 0; i < ini->section_count; i++) {
        fprintf(file, "[%s]\n", ini->sections[i].section);
        for (int j = 0; j < ini->sections[i].pair_count; j++) {
            fprintf(file, "%s=%s\n", ini->sections[i].pairs[j].key, ini->sections[i].pairs[j].value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void FileManager::free_ini(IniFile* ini) {
    for (int i = 0; i < ini->section_count; i++) {
        free(ini->sections[i].pairs);
    }
    free(ini->sections);
    free(ini);
}

void FileManager::initialize_default_values(IniFile* ini) {
    set_value(ini, "Login", "username", "guest");
    set_value(ini, "Login", "password", "1234");

    set_value(ini, "Account", "balance", "0");
    set_value(ini, "Account", "account_number", "000000");

    set_value(ini, "Settings", "language", "pt-BR");
    set_value(ini, "Settings", "theme", "none");

    save_ini(ini, "config.ini");
}