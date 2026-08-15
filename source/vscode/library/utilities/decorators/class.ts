/// Package Modules
import { Inversify } from '../vendors';

/** Class-Based Decorators */
export namespace Class {
    //  DECORATORS  //

    /**
     * Renames a target class.
     * @param name                  Name to bind.
     */
    export const Rename =
        (name: string) =>
        <T extends abstract new (...args: any[]) => any>(Target: T) => {
            @Inversify.injectable() // ensure still injectable
            abstract class Indirection extends Target {} // prepare the indirection
            const Renamed = { [name]: class extends Indirection {} }[name];
            return Inversify.decorate(Inversify.injectable as any, Renamed);
        };
}
