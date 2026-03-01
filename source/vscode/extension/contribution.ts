/// Talos Modules
import { Dependency, Disposable } from '../utilities';

/** Extension Contribution Interface. */
export const Contribution = Dependency.Name('extension.contribution');
export interface Contribution extends Disposable.Maybe {
    readonly constructor: NewableFunction;

    configure?(): Promise<void>;
    activate?(): Promise<void>;
}

export namespace Contribution {
    //  TYPEDEFS  //

    /** Available Contribution Actions. */
    export type Action = keyof Omit<Contribution, 'constructor' | 'dispose'>;
}
