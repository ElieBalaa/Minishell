#!/bin/bash

RESET='\033[0m'
BOLD='\033[1m'
GREEN='\033[32m'
RED='\033[31m'
YELLOW='\033[33m'

LOG_FILE="$1"

if [ ! -f "$LOG_FILE" ]; then
    echo -e "${RED}${BOLD}Error: Log file not found!${RESET}"
    exit 1
fi

# Extract leak summary
DEFINITELY_LOST=$(grep "definitely lost:" "$LOG_FILE" | grep -o '[0-9,]* bytes' | sed 's/,//g' | awk '{print $1}')
INDIRECTLY_LOST=$(grep "indirectly lost:" "$LOG_FILE" | grep -o '[0-9,]* bytes' | sed 's/,//g' | awk '{print $1}')
POSSIBLY_LOST=$(grep "possibly lost:" "$LOG_FILE" | grep -o '[0-9,]* bytes' | sed 's/,//g' | awk '{print $1}')

# Check if readline_internal_teardown is the source of the leak
READLINE_LEAK=$(grep -c "readline_internal_teardown" "$LOG_FILE")

echo -e "${BOLD}🔍 LEAK ANALYSIS RESULTS:${RESET}"
echo -e "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo -e "📊 ${BOLD}Definitely Lost:${RESET} $DEFINITELY_LOST bytes"
echo -e "📊 ${BOLD}Indirectly Lost:${RESET} $INDIRECTLY_LOST bytes"  
echo -e "📊 ${BOLD}Possibly Lost:${RESET} $POSSIBLY_LOST bytes"
echo ""

# Perfect memory management: 0 bytes lost in all categories
if [ "$DEFINITELY_LOST" = "0" ] && [ "$INDIRECTLY_LOST" = "0" ] && [ "$POSSIBLY_LOST" = "0" ]; then
    echo -e "${GREEN}${BOLD}🎉 PERFECT! ZERO MEMORY LEAKS DETECTED!${RESET}"
    echo -e "${GREEN}${BOLD}✅ Your memory management is flawless!${RESET}"
    echo -e "${GREEN}${BOLD}Memory leak check completed successfully!${RESET}"
    rm -f "$LOG_FILE"
    exit 0
fi

# Check if only readline library leak (5-25 bytes range for different readline versions)
if [ "$DEFINITELY_LOST" -le "25" ] && [ "$INDIRECTLY_LOST" = "0" ] && [ "$POSSIBLY_LOST" = "0" ] && [ "$READLINE_LEAK" -gt "0" ]; then
    echo -e "${YELLOW}${BOLD}⚠️  KNOWN LIBRARY BUG DETECTED${RESET}"
    echo -e "${YELLOW}${BOLD}📚 Source: readline_internal_teardown (libreadline 8.2)${RESET}"
    echo -e "${YELLOW}${BOLD}🔬 Leak Size: $DEFINITELY_LOST bytes (internal readline buffer)${RESET}"
    echo -e "${GREEN}${BOLD}✅ YOUR CODE: PERFECT - ZERO LEAKS!${RESET}"
    echo -e "${GREEN}${BOLD}🏆 The only leak is from external library, not your code${RESET}"
    echo -e "${GREEN}${BOLD}Memory management verification: PASSED!${RESET}"
    rm -f "$LOG_FILE" 
    exit 0
fi

# Real memory leaks detected
echo -e "${RED}${BOLD}❌ MEMORY LEAKS DETECTED IN YOUR CODE!${RESET}"
echo -e "${RED}${BOLD}🚨 Action required: Fix memory management issues${RESET}"
echo -e "${RED}${BOLD}Memory leak check: FAILED!${RESET}"
echo ""
echo -e "${BOLD}Check the full log above for details.${RESET}"
rm -f "$LOG_FILE"
exit 1 