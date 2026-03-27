/// Node Modules
import * as fs from 'node:fs';

/// Website Modules
import { Assets } from '@/website/assets';

/// Package Modules
import { Descriptor } from '../descriptor';

/** Builtins Registry Namespace. */
export namespace Registry {
    //  PUBLIC METHODS  //

    /** Resolves a list of all builtins. */
    export function list(): Descriptor[] {
        // prepare the source directory of builtins
        const source = Assets.builtins();

        console.log('Builtins:', Assets.builtins());
        console.log(fs.readdirSync(source));

        // filter all the available files now
        return fs
            .readdirSync(source)
            .map(resolve)
            .filter((builtin): builtin is Descriptor => typeof builtin === 'object');
    }

    /**
     * Handles resolving builtin documentation.
     * @param name                  Name of builtin.
     */
    export function resolve(name: string): Descriptor | undefined {
        // immediately stop invalid items
        if (name.startsWith('_')) return;

        // attempt finding the necessary crate now
        const builtin = Assets.builtins(name);
        if (!fs.existsSync(builtin)) return;

        // ensure the given name is valid now
        if (builtin.includes('.')) return;

        // since value, then resolve a suitable set of details
        return { name: name[0].toUpperCase() + name.slice(1) };
    }
}
