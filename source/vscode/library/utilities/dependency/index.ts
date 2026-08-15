/// VSC Modules
import { Product } from '@/vscode/product';

/// Package Modules
import { Inversify } from '../vendors';

/** Dependency Provider. */
export interface Dependency<T> extends Dependency.Provider<T> {}
export namespace Dependency {
    //  TYPEDEFS  //

    /** Dependency Name Typing. */
    export type Name = string | number | symbol;
    export const Name = (label: string) => Symbol(`${Product.identifier}/${label}`);

    /** Dependency Provider Interface. */
    export const Provider = Name('dependency.provider');
    export interface Provider<T> {
        get length(): number;
        get(): ReadonlyArray<T>;
        values(): ArrayIterator<T>;
        [Symbol.iterator](): ArrayIterator<T>;
    }

    //  IMPLEMENTATIONS  //

    /** Internal Provider Implemenation. */
    class Internal<T> implements Provider<T> {
        //  PROPERTIES  //

        /** Currently bound dependencies. */
        private m_dependencies?: T[];

        //  GETTERS x SETTERS  //

        /** Gets the length of the provider. */
        get length() {
            return this.get().length;
        }

        //  CONSTRUCTORS  //

        /**
         * Constructs an internal provider.
         * @param m_identifier              Service identifier.
         * @param m_container               Services container.
         */
        constructor(
            private readonly m_identifier: Inversify.ServiceIdentifier<T>,
            private readonly m_options: Inversify.ContainerModuleLoadOptions,
            private readonly m_context: Inversify.ResolutionContext,
        ) {}

        //  SYMBOL METHODS  //

        /** Handles getting the iterator details. */
        [Symbol.iterator]() {
            return this.get()[Symbol.iterator]();
        }

        //  PUBLIC METHODS  //

        /** Gets the list of dependencies. */
        get() {
            // pre-resolve the dependencies if they already have been gotten
            if (Array.isArray(this.m_dependencies)) return this.m_dependencies;

            // if not attached, then do so now as necessary
            if (!this.m_options.isBound(this.m_identifier)) return (this.m_dependencies = []);

            // attempt scanning for the available dependencies now
            return (this.m_dependencies = this.m_context.getAll(this.m_identifier));
        }

        /** Handles getting the current dependencies. */
        values() {
            return this.get().values();
        }
    }

    //  PUBLIC METHODS  //

    /**
     * Handles injecting named dependencies.
     * @param name                  Name of dependency.
     */
    export const inject = (name: Name) => {
        const named = Inversify.named(name) as any;
        const bind = Inversify.inject(Provider) as any;

        // return the resulting injection handler now
        return (target: any, key?: string | symbol | undefined, descriptor?: number | PropertyDescriptor): void => {
            bind(target, key, descriptor);
            named(target, key, descriptor);
        };
    };

    /**
     * Handles coupling dependencies.
     * @param options                       Container module options.
     * @param name                          Name of dependency.
     */
    export const couple = (_: Inversify.ContainerModuleLoadOptions, name: Name) => {
        const binding = _.bind(Provider).toDynamicValue((ctx) => new Internal(name as any, _, ctx));
        binding.inSingletonScope().whenNamed(name); // and ensure fully bound as necessary
    };
}

/** Base Container Instance. */
export const Container = Dependency.Name('dependency.container');
export interface Container extends Inversify.Container {}
