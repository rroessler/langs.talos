/// Package Modules
import { Property } from '../property';

/** Builtins Descriptor Interface. */
export interface Descriptor extends Property {
    readonly fields?: Property[];
    readonly statics?: Property[];
}
