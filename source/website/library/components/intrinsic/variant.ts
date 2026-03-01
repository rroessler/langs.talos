/** Intrinsic Color Variants. */
export type Variant = 'primary' | 'secondary';
export function Variant<T>(variant: Variant, items: Record<Variant, T>) {
    return items[variant];
}
