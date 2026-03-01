//  DECORATORS  //

export function Memoize() {
    // prepare the underlying weak mapping
    const instances = new WeakMap();

    // attempt building the necessary descriptor
    return (target: any, property: string, descriptor: PropertyDescriptor) => {
        const input = target[property]; // get the underlying functor to be used
        if (typeof input !== 'function') throw new TypeError('The decorated value must be a function');

        delete descriptor.value;
        delete descriptor.writable;

        // override the underlying handler for memoization
        descriptor.get = function () {
            if (instances.has(this)) return instances.get(this);
            return instances.set(input, Memoize.wrap(input)).get(this);
        };
    };
}

//  NAMESPACES  //

export namespace Memoize {
    //  TYPEDEFS  //

    /** Underlying Target Function. */
    export type Target = (...args: readonly any[]) => unknown;

    /** Storage Item Interface. */
    export interface Item<T> {
        readonly data: T;
    }

    //  PUBLIC METHODS  //

    /**
     * Handles wrapping a memoization target.
     * @param target            Target to memoize.
     */
    export const wrap = <T extends Target>(target: T): T => {
        // prepare the storage container to be used
        const storage = new Map<any, Item<ReturnType<T>>>();

        // and construct the memoize handler to be used now
        return function (this: any, ...args: Parameters<T>[]): ReturnType<T> {
            const key = args[0]; // compute
            const item = storage.get(key);
            if (item) return item.data;

            const result = target.apply(this, args) as ReturnType<T>;
            return storage.set(key, { data: result }), result;
        } as T;
    };
}
