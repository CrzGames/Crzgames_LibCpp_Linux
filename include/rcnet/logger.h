#ifndef RCNET_LOGGER_H
#define RCNET_LOGGER_H

#include <stdarg.h> // Required for : ... (va_list, va_start, va_end, vsnprintf)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enum définissant les niveaux de journalisation personnalisés.
 * @typedef {enum} RCNET_LogLevel
 * @property {number} RCNET_LOG_DEBUG - Messages de débogage.
 * @property {number} RCNET_LOG_INFO - Messages informatifs.
 * @property {number} RCNET_LOG_WARN - Messages d'avertissement.
 * @property {number} RCNET_LOG_ERROR - Messages d'erreur.
 * @property {number} RCNET_LOG_CRITICAL - Messages d'erreur critique.
 */
typedef enum RCNET_LogLevel {
    RCNET_LOG_DEBUG,    
    RCNET_LOG_INFO,      
    RCNET_LOG_WARN,      
    RCNET_LOG_ERROR,    
    RCNET_LOG_CRITICAL   
} RCNET_LogLevel;

void rcnet_log_set_priority(const RCNET_LogLevel logLevel);
void rcnet_log(const RCNET_LogLevel logLevel, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif // RCNET_LOGGER_H
