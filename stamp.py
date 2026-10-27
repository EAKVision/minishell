import os
import datetime

HEADER_TEMPLATE = """/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   {filename:<48}       :+:      :+:    :+:   */
/*                                                    :+:      :+:    :+:   */
/*   By: Amr Khedr (ELITE AKV) <amr.f.khedr@gmail.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 01:00:00 by akhedr            #+#    #+#             */
/*   Updated: 2026/10/28 01:00:00 by akhedr           ###   ########.fr       */
/*                                                                            */
/*   Copyright (c) 2026 Amr Khedr. All Rights Reserved.                      */
/* ************************************************************************** */

"""

def stamp_files():
    current_date = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")
    for root, dirs, files in os.walk("."):
        # Skip hidden directories like .git
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for file in files:
            if file.endswith((".c", ".h")):
                filepath = os.path.join(root, file)
                with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                
                # Check if header is already present
                if "Amr Khedr (ELITE AKV)" in content:
                    print(f"[Skipped] Already stamped: {filepath}")
                    continue
                
                # Format header with exact filename
                formatted_header = HEADER_TEMPLATE.format(filename=file)
                
                with open(filepath, "w", encoding="utf-8") as f:
                    f.write(formatted_header + content)
                print(f"[Stamped] {filepath}")

if __name__ == "__main__":
    stamp_files()
