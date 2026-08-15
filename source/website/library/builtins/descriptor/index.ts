/// Package Modules
import { Property } from '../property';

/** Extra Documentation Record. */
export interface Ancillary {
    [key: `${'fields' | 'statics'}.${string}`]: React.ReactNode;
}

/** Builtins Descriptor Interface. */
export interface Descriptor extends Property {
    readonly fields?: Property[];
    readonly statics?: Property[];
}
