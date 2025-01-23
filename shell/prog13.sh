#!/bin/bash
# Script to display processes that are in the sleeping state (status 'S')

echo "Processes in Sleeping State (Status 'S'):"
echo "----------------------------------------"
ps aux | awk '$8 ~ /^S/ {print $0}'
