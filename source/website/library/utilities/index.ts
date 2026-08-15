/// Vendor Modules
import { type ClassValue, clsx } from 'clsx';
import { twMerge } from 'tailwind-merge';

/**
 * Handles merging dynamic class-names.
 * @param inputs                Inputs to bind.
 */
export function cn(...inputs: ClassValue[]) {
    return twMerge(clsx(inputs));
}
